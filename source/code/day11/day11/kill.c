/*
 * kill.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void fa(int signo){
  printf("捕获了信号%d\n",signo);
}
int main(){
  pid_t pid = fork();
  if(pid == 0){
		signal(SIGINT,fa);
		sleep(10);
	  printf("child over\n");
	  exit(0);
	}
	sleep(1);
  kill(pid,SIGINT);
	printf("father over\n");
}

