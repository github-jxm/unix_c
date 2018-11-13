/*
* /alarm.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void fa(int signo){
  printf("时间到了，该起床了\n");
	//exit(0);
	alarm(1);
}
int main(){
	signal(SIGALRM,fa);
	alarm(3);//3秒后发送信号SIGALRM
	//alarm(0);//取消闹钟
  while(1);
}

