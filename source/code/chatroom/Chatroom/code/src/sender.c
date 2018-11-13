// 聊天室发送器
//
#include "chatroom.h"

// 启动
int start (const char* ip, unsigned short port, const char* nickname) {
	printf ("发送器：创建网络流套接字...\n");

	int sockfd = socket (AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror ("socket");
		return -1;
	}

	printf ("发送器：准备地址并连接...\n");

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons (port);
	addr.sin_addr.s_addr = inet_addr (ip);
	if (connect (sockfd, (struct sockaddr*)&addr, sizeof (addr)) == -1) {
		perror ("connect");
		return -1;
	}

	// 向服务器发送标志包
	char tag[MAX_TAG] = "SNDR";
	strcat (tag, nickname);
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
		printf ("发送器：服务器已宕机！\n");
		return -1;
	}

	// 服务器返回错误信息
	if (strncmp (ack, "OK", 2)) {
		printf ("服务器：%s\n", ack);
		return -1;
	}

	return sockfd;
}

// 运行
int run (int sockfd, const char* nickname) {
	printf ("发送器：发送信息...\n");

	for (;;) {
		printf ("%s> ", nickname);

		char txt[MAX_TXT];
		gets (txt); // 读取控制台输入

		if (strspn (txt, " \t\r\n") == strlen (txt)) {
			printf ("发送器：请不要输入空白字符串！\n");
			continue;
		}

		if (! strcmp (txt, "!"))
			break;

		// 向服务器发送文本包
		if (send (sockfd, txt, (strlen (txt) + 1) * sizeof (txt[0]), 0) == -1) {
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
			printf ("发送器：服务器已宕机！\n");
			break;
		}
	}

	return 0;
}

// 停止
int stop (int sockfd) {
	printf ("发送器：关闭套接字...\n");

	if (close (sockfd) == -1) {
		perror ("close");
		return -1;
	}

	printf ("发送器：再见！\n");

	return 0;
}

int main (int argc, char* argv[]) {
	if (argc < 4) {
		fprintf (stderr, "用法：%s <服务器IP地址> <端口号> <昵称>\n", argv[0]);
		return -1;
	}

	printf ("********************\n");
	printf ("* 狂聊聊天室发送器 *\n");
	printf ("********************\n");

	// 启动
	int sockfd = start (argv[1], atoi (argv[2]), argv[3]);
	if (sockfd == -1)
		return -1;

	// 运行
	if (run (sockfd, argv[3]) == -1)
		return -1;

	// 停止
	return stop (sockfd);
}
