
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
		FILE *fp = fopen("/etc/passwd", "r+");
		if(fp == NULL)
		{
				//printf("open /etc/passwd 失败：%s\n", 
				//				strerror(errno));
				//perror("open /etc/passwd failed");
				printf("error: %m\n");

		}
		else
		{
			printf("打开文件passwd成功\n");
		}
		return 0;
		
}
