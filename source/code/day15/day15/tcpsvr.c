/*
 * tcpsvr.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void sigchld (int signum) {
	wait (0);
	printf ("回收了一个子进程的尸体！\n");
}
int main (int argc, char* argv[]) {
	if (argc < 2) {
		printf ("用法：%s <端口号>\n", argv[0]);
		return -1;
	}
	if (signal (SIGCHLD, sigchld) == SIG_ERR) {
		perror ("signal");
		return -1;
	}
	printf ("服务器：创建套接字...\n");
	int sockfd = socket (AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror ("socket");
		return -1;
	}
	printf ("服务器：准备地址并绑定...\n");
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons (atoi (argv[1]));
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind (sockfd, (struct sockaddr*)&addr,
		sizeof (addr)) == -1) {
		perror ("bind");
		return -1;
	}
	printf ("服务器：监听套接字...\n");
	if (listen (sockfd, 1024) == -1) {
		perror ("listen");
		return -1;
	}
	for (;;) {
		printf ("服务器：等待连接请求...\n");
		struct sockaddr_in addrcli = {};
		socklen_t addrlen = sizeof (addrcli);
		int connfd = accept (sockfd, (struct sockaddr*)&addrcli, &addrlen);
		printf ("服务器：接受来自%s:%u客户机的"
			"连接请求。\n",
			inet_ntoa (addrcli.sin_addr),
			ntohs (addrcli.sin_port));

		pid_t pid = fork ();
		if (pid == -1) {
			perror ("fork");
			return -1;
		}
		if (pid == 0) {
			printf ("服务器：收发数据...\n");
			for (;;) {
				char buf[1024];
				ssize_t rb = recv (connfd, buf, sizeof (buf), 0);
				if (rb == -1) {
					perror ("recv");
					return -1;
				}
				if (rb == 0) {
					printf ("服务器："
						"客户机已关闭连接。\n");
					break;
				}
				if (send (connfd, buf, rb, 0) == -1) {
					perror ("send");
					return -1;
				}
			}
			printf ("服务器：关闭套接字...\n");
			close (connfd);
			return 0;
		}
	}
	close (sockfd);
	return 0;
}
