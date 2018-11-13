/*
 * sleep.c
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void fa(int signo){
  printf("捕获了信号%d\n",signo);
}
int main(){
	signal(SIGINT,fa);
  printf("开始休眠\n");
	int res = sleep(10);
	if(res == 0) printf("睡的好\n");
	else printf("被打断了，剩余%d秒\n",res);
	usleep(10000);//0.01秒
	printf("很快\n");
}

