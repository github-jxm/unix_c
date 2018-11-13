// 聊天室接收器
//
#include "chatroom.h"

// SIGINT信号处理函数
void sigint (int signum) {
	printf ("\n接收器：再见！\n");
	exit (0);
}

// 启动
int start (const char* ip, unsigned short port) {
	if (signal (SIGINT, sigint) == SIG_ERR) {
		perror ("signal");
		return -1;
	}

	printf ("接收器：创建网络流套接字...\n");

	int sockfd = socket (AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror ("socket");
		return -1;
	}

	printf ("接收器：准备地址并连接...\n");

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons (port);
	addr.sin_addr.s_addr = inet_addr (ip);

	if (connect (sockfd, (struct sockaddr*)&addr, sizeof (addr)) == -1) {
		perror ("connect");
		return -1;
	}

	// 向服务器发送标志包
	char tag[MAX_TAG] = "RCVR";
	if (send (sockfd, tag, (strlen (tag) + 1) * sizeof (tag[0]), 0) == -1) {
		perror ("send");
		return -1;
	}

	// 从服务器接收应答包
	char ack[MAX_ACK];
	ssize_t rb = recv (sockfd, ack, sizeof (ack), 0);
	if (rb == -1) {
		perror ("recv");
		return -1;
	}
	if (rb == 0) {
		printf ("接收器：服务器已宕机！\n");
		return -1;
	}

	return sockfd;
}

// 运行
int run (int sockfd) {
	printf ("接收器：接收信息...\n");

	for (;;) {
		// 从服务器接收消息包
		char msg[MAX_MSG];
		ssize_t rb = recv (sockfd, msg, sizeof (msg), 0);
		if (rb == -1) {
			perror ("recv");
			return -1;
		}
		if (rb == 0) {
			printf ("接收器：服务器已宕机！\n");
			break;
		}

		// 打印消息包
		printf ("%s\n", msg);

		// 向服务器发送应答包
		char ack[MAX_ACK] = "OK";
		if (send (sockfd, ack, (strlen (ack) + 1) * sizeof (ack[0]), 0) == -1) {
			perror ("send");
			return -1;
		}
	}

	return 0;
}

// 停止
int stop (int sockfd) {
	printf ("接收器：关闭套接字...\n");

	if (close (sockfd) == -1) {
		perror ("close");
		return -1;
	}

	printf ("接收器：再见！\n");

	return 0;
}

int main (int argc, char* argv[]) {
	if (argc < 3) {
		fprintf (stderr, "用法：%s <服务器IP地址> <端口号>\n", argv[0]);
		return -1;
	}

	printf ("********************\n");
	printf ("* 狂聊聊天室接收器 *\n");
	printf ("********************\n");

	// 启动
	int sockfd = start (argv[1], atoi (argv[2]));
	if (sockfd == -1)
		return -1;

	// 运行
	if (run (sockfd) == -1)
		return -1;

	// 停止
	return stop (sockfd);
}
