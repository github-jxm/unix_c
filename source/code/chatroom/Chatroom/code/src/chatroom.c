// 聊天室服务器
//
#include "chatroom.h"

// 发送器结构体
typedef struct Sender {
	int  connfd;            // 发送器连接套接字
	char nickname[MAX_NCK]; // 发送器昵称
}	SENDER;

LIST* g_snds = NULL; // 发送器结构体列表
LIST* g_rcvs = NULL; // 接收器套接字列表
LIST* g_msgs = NULL; // 消息包队列

// 发送器结构体列表互斥量
pthread_mutex_t g_mtx_snds = PTHREAD_MUTEX_INITIALIZER;
// 接收器套接字列表互斥量
pthread_mutex_t g_mtx_rcvs = PTHREAD_MUTEX_INITIALIZER;
// 消息包队列互斥量
pthread_mutex_t g_mtx_msgs = PTHREAD_MUTEX_INITIALIZER;
// 消息包队列非空条件变量
pthread_cond_t  g_cnd_msgs = PTHREAD_COND_INITIALIZER;

// SIGINT信号处理函数
void sigint (int signum) {
	printf ("\n服务器：再见！\n");
	exit (0);
}

// 从消息包队列弹出消息
char* pop_msg (void) {
	pthread_mutex_lock (&g_mtx_msgs);
	while (list_empty (g_msgs)){
		pthread_cond_wait (&g_cnd_msgs, &g_mtx_msgs);
	}
	char* msg = (char*)list_pop (g_msgs);
	pthread_mutex_unlock (&g_mtx_msgs);
	return msg;
}

// 向消息包队列压入消息
void push_msg (char* msg) {
	pthread_mutex_lock (&g_mtx_msgs);
	list_push (g_msgs, msg);
	pthread_cond_broadcast (&g_cnd_msgs);
	pthread_mutex_unlock (&g_mtx_msgs);
}

// 发送线程过程函数
void* send_proc (void* arg) {
	// 发送循环
	for (;;) {
		char* msg = pop_msg (); // 从消息包对列中弹出消息
		pthread_mutex_lock (&g_mtx_rcvs);

		// 遍历接收器套接字列表
		list_begin (g_rcvs);
		while (! list_end (g_rcvs)) {
			int* connfd = (int*)list_next (g_rcvs); // 针对每一个接收器

			// 向接收器发送消息包
			if (send (*connfd, msg, (strlen (msg) + 1) * sizeof (msg[0]), 0) == -1) {
				perror ("send");
				close (*connfd);
				*connfd = -1;
				continue;
			}

			// 从接收器接收应答包
			char ack[MAX_ACK];
			ssize_t rb = recv (*connfd, ack, sizeof (ack), 0);
			if (rb == -1) {
				perror ("recv");
				close (*connfd);
				*connfd = -1;
				continue;
			}
			if (rb == 0) {
				printf ("服务器：接收器已关闭连接。\n");
				close (*connfd);
				*connfd = -1;
				continue;
			}
		}

		// 从接收器套接字列表中删除已失效的接收器套接字
		list_remove (g_rcvs, (void*)-1);

		pthread_mutex_unlock (&g_mtx_rcvs);
		free (msg); // 销毁已发送的消息包
	}

	return NULL;
}

// 发送器登入
void login (const SENDER* sender) {
	pthread_mutex_lock (&g_mtx_snds);
	list_push (g_snds, (void*)sender);
	pthread_mutex_unlock (&g_mtx_snds);
}

// 发送器登出
void logout (const SENDER* sender) {
	pthread_mutex_lock (&g_mtx_snds);
	list_remove (g_snds, (void*)sender);
	pthread_mutex_unlock (&g_mtx_snds);
}

// 接收线程过程函数
void* recv_proc (void* arg) {
	SENDER* sender = (SENDER*)arg;
	login (sender);

	// 向消息包队列压入欢迎包
	char* msg = malloc (MAX_MSG * sizeof (char));
	sprintf (msg, "系统> 热烈欢迎%s进入聊天室！", sender->nickname);
	push_msg (msg);

	// 接收循环
	for (;;) {
		// 从发送器接收文本包
		char txt[MAX_TXT];
		ssize_t rb = recv (sender->connfd, txt, sizeof (txt), 0);
		if (rb == -1) {
			perror ("recv");
			break;
		}
		if (rb == 0) {
			printf ("服务器：发送器已关闭连接。\n");

			// 向消息包队列压入告别包
			char* msg = malloc (MAX_MSG * sizeof (char));
			sprintf (msg, "系统> %s挥一挥衣袖，不带走一片云彩...",
				sender->nickname);
			push_msg (msg);
			break;
		}

		// 向消息包队列压入文本包
		char* msg = malloc (MAX_MSG * sizeof (char));
		sprintf (msg, "%s> %s", sender->nickname, txt);
		push_msg (msg);

		// 向发送器发送应答包
		char ack[MAX_ACK] = "OK";
		if (send (sender->connfd, ack, (strlen (ack) + 1) *
			sizeof (ack[0]), 0) == -1) {
			perror ("send");
			break;
		}
	}

	logout (sender);
	close (sender->connfd);
	free (sender);

	return NULL;
}

// 启动发送线程
int start_send (void) {
	printf ("服务器：启动发送线程...\n");

	int error;
	pthread_attr_t attr;

	if ((error = pthread_attr_init (&attr)) != 0) {
		fprintf (stderr, "pthread_attr_init: %s\n",
			strerror (error));
		return -1;
	}

	if ((error = pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED)) != 0) {
		fprintf (stderr, "pthread_attr_setdetachstate: %s\n", strerror (error));
		return -1;
	}

	pthread_t tid;
	if ((error = pthread_create (&tid, &attr, send_proc, NULL)) != 0) {
		fprintf (stderr, "pthread_create: %s\n", strerror (error));
		return -1;
	}

	if ((error = pthread_attr_destroy (&attr)) != 0) {
		fprintf (stderr, "pthread_attr_destroy: %s\n", strerror (error));
		return -1;
	}

	return 0;
}

// 启动
int start (unsigned short port) {
	if (signal (SIGINT, sigint) == SIG_ERR) {
		perror ("signal");
		return -1;
	}

	printf ("服务器：创建网络流套接字...\n");

	int sockfd = socket (AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror ("socket");
		return -1;
	}

	int on = 1;
	if (setsockopt (sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof (on)) == -1) {
		perror ("setsockopt");
		return -1;
	}

	printf ("服务器：准备地址并绑定...\n");

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons (port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind (sockfd, (struct sockaddr*)&addr, sizeof (addr)) == -1) {
		perror ("bind");
		return -1;
	}

	printf ("服务器：监听套接字...\n");

	if (listen (sockfd, 1024) == -1) {
		perror ("listen");
		return -1;
	}

	g_snds = list_create ();
	g_rcvs = list_create ();
	g_msgs = list_create ();

	// 启动发送线程
	if (start_send () == -1)
		return -1;

	return sockfd; // 返回监听套接字
}

// 昵称可用否
int verify (const char* nickname) {
	int ok = 1;
	pthread_mutex_lock (&g_mtx_snds);

	// 遍历发送器结构体列表
	list_begin (g_snds);
	while (! list_end (g_snds)) {
		// 针对每一个发送器
		if (! strcmp ((**(SENDER**)list_next (g_snds)).nickname,
			nickname)) {
			ok = 0;
			break;
		}
	}

	pthread_mutex_unlock (&g_mtx_snds);
	return ok;
}

// 等待客户机连接
int wait_client (int sockfd, char nickname[]) {
	printf ("服务器：等待连接请求...\n");

	// 接受来自客户机的连接请求
	struct sockaddr_in addrcli;
	socklen_t addrlen = sizeof (addrcli);
	int connfd = accept (sockfd, (struct sockaddr*)&addrcli, &addrlen);
	if (connfd == -1) {
		perror ("accept");
		return -1;
	}

	// 从客户机接收标志包
	char tag[MAX_TAG];
	if (recv (connfd, tag, MAX_TAG, 0) == -1) {
		perror ("recv");
		close (connfd);
		return -2;
	}

	char ack[MAX_ACK] = "OK";

	// 发送器
	if (! strncmp (tag, "SNDR", 4))
		if (verify (tag + 4)) {
			printf ("服务器：接受来自%s:%u发送器的连接请求。\n",
					inet_ntoa (addrcli.sin_addr), ntohs (addrcli.sin_port));
			strcpy (nickname, tag + 4);
		}
		else {
			printf ("服务器：拒绝来自%s:%u发送器的连接请求。\n",
					inet_ntoa (addrcli.sin_addr), ntohs (addrcli.sin_port));
			strcpy (ack, "更换昵称再试一次！");
		}
	// 接收器
	else if (! strncmp (tag, "RCVR", 4))
		printf ("服务器：接受来自%s:%u接收器的连接请求。\n",
				inet_ntoa (addrcli.sin_addr), ntohs (addrcli.sin_port));
	// 非法客户机
	else {
		printf ("服务器：拒绝来自%s:%u客户机的连接请求。\n",
				inet_ntoa (addrcli.sin_addr), ntohs (addrcli.sin_port));
		close (connfd);
		return -2;
	}

	// 向客户机发送应答包
	if (send (connfd, ack, (strlen (ack) + 1) * sizeof (ack[0]), 0) == -1) {
		perror ("send");
		close (connfd);
		return -2;
	}

	if (strcmp (ack, "OK")) {
		close (connfd);
		return -2;
	}

	return connfd; // 返回连接套接字
}

// 启动接收线程
int start_recv (int connfd, const char* nickname) {
	printf ("服务器：启动接收线程...\n");

	int error;
	pthread_attr_t attr;

	if ((error = pthread_attr_init (&attr)) != 0) {
		fprintf (stderr, "pthread_attr_init: %s\n", strerror (error));
		return -1;
	}

	if ((error = pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED)) != 0) {
		fprintf (stderr, "pthread_attr_setdetachstate: %s\n", strerror (error));
		return -1;
	}

	// 初始化发送器结构体，填入发送器信息，
	// 包括与之连接的套接字
	SENDER* sender = malloc (sizeof (SENDER));
	sender->connfd = connfd;
	strcpy (sender->nickname, nickname);

	// 每个接收线程持有一个发送器结构体，
	// 为该发送器提供服务
	pthread_t tid;
	if ((error = pthread_create (&tid, &attr, recv_proc, sender)) != 0) {
		fprintf (stderr, "pthread_create: %s\n", strerror (error));
		return -1;
	}

	if ((error = pthread_attr_destroy (&attr)) != 0) {
		fprintf (stderr, "pthread_attr_destroy: %s\n", strerror (error));
		return -1;
	}

	return 0;
}

// 运行
int run (int sockfd) {
	for (;;) {
		// 等待客户机连接，返回与客户机连接的套接字
		char nickname[MAX_NCK] = {};
		int connfd = wait_client (sockfd, nickname);
		if (connfd == -1)
			return -1;
		else
		if (connfd == -2)
			continue;

		// 针对来自发送器的连接
		if (strlen (nickname)) {
			// 启动接收线程
			if (start_recv (connfd, nickname) == -1) {
				close (connfd);
				continue;
			}
		}
		// 针对来自接收器的连接
		else {
			// 将与接收器连接的套接字加入接收器套接字列表
			pthread_mutex_lock (&g_mtx_rcvs);
			list_push (g_rcvs, (void*)connfd);
			pthread_mutex_unlock (&g_mtx_rcvs);
		}
	}
}

// 停止
int stop (int sockfd) {
	list_destroy (g_msgs);
	list_destroy (g_rcvs);
	list_destroy (g_snds);

	printf ("服务器：关闭套接字...\n");

	if (close (sockfd) == -1) {
		perror ("close");
		return -1;
	}

	printf ("服务器：再见！\n");

	return 0;
}

// 主函数
int main (int argc, char* argv[]) {
	if (argc < 2) {
		fprintf (stderr, "用法：%s <端口号>\n", argv[0]);
		return -1;
	}

	printf ("********************\n");
	printf ("* 狂聊聊天室服务器 *\n");
	printf ("********************\n");

	// 启动
	int sockfd = start (atoi (argv[1]));
	if (sockfd == -1)
		return -1;

	// 运行
	if (run (sockfd) == -1)
		return -1;

	// 停止
	return stop (sockfd);
}
