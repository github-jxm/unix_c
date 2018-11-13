/*
 * vfork.c
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
  pid_t pid = vfork();
	if(pid==0){
	  printf("cpid=%d\n",getpid());
		execl("./proc","proc",NULL);
	}
  printf("father over\n");
}

