#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void fa(int signo) //参数系统自动传入信号值
{
  printf("捕获了信号%d\n",signo);
}
int main()
{
	signal(SIGINT,fa);//把信号2的处理方式改为fa
	if(signal(SIGQUIT,SIG_IGN)==SIG_ERR)
		perror("signal3"),exit(-1);
	signal(9,fa);//9只能默认处理,改动无效
	printf("pid=%d\n",getpid());
	while(1);
}


