/*
 * sigprocmask.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void fa(int signo){
  printf("捕获了信号%d\n",signo);
}
int main(){
	printf("pid=%d\n",getpid());
  signal(SIGINT,fa); signal(50,fa);
  printf("执行普通代码，没有屏蔽信号\n");
	sleep(15);
  printf("执行关键代码，开始屏蔽信号\n");
  sigset_t set,old; sigemptyset(&set); 
	sigaddset(&set,2);sigaddset(&set,50);
  int res=sigprocmask(SIG_SETMASK,&set,&old);
	if(res==-1) perror("sigmask"),exit(-1);
  sleep(15);
	/*sigset_t pend;
	sigpending(&pend);
  if(sigismember(&pend,2))
		printf("信号2来过\n");*/
  printf("关键代码结束，解除信号屏蔽\n");
	sigprocmask(SIG_SETMASK,&old,NULL);
	sleep(15);
}

