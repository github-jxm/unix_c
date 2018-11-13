/*
 * tcpcli.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main (int argc, char* argv[]) {
	if (argc < 3) {
		printf ("用法：%s <IP地址> <端口号>\n",
			argv[0]);
		return 0;
	}
	printf ("客户机：创建套接字...\n");
	int sockfd = socket (AF_INET, SOCK_STREAM,
		0);
	if (sockfd == -1) {
		perror ("socket");
		return -1;
	}
	printf ("客户机：准备地址并连接...\n");
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons (atoi (argv[2]));
	addr.sin_addr.s_addr = inet_addr (argv[1]);
	if (connect (sockfd, (struct sockaddr*)&addr, sizeof (addr)) == -1) {
		perror ("connect");
		return -1;
	}
	printf ("客户机：收发数据...\n");
	for (;;) {
		printf ("> ");
		char buf[1024];
		gets (buf);
		if (! strcmp (buf, "!"))
			break;
		if (send (sockfd, buf, strlen (buf) + 1, 0) == -1) {
			perror ("send");
			return -1;
		}
		memset (buf, 0, sizeof (buf));
		ssize_t rb = recv (sockfd, buf,
			sizeof (buf), 0);
		if (rb == -1) {
			perror ("recv");
			return -1;
		}
		if (rb == 0) {
			printf ("客户机：服务器已宕机！\n");
			break;
		}
		printf ("< %s\n", buf);
	}
	printf ("客户机：关闭套接字...\n");
	close (sockfd);
	return 0;
}
