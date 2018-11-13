/*
 * fork.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void fa(int signo){
  printf("捕获了信号%d\n",signo);
}
int main(){
  signal(SIGINT,fa);
	signal(SIGQUIT,SIG_IGN);
	//printf("begin\n");
  pid_t pid = fork();
	//printf("end\n");
	if(pid==0){
		//signal(SIGINT,SIG_DFL);
	  printf("cpid=%d\n",getpid());
		while(1);
	}
	printf("father over\n");
}//练习: 测试vfork()+execl() 信号继承效果

