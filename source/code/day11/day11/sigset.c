/*
 * sigset.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(){
  sigset_t set;
	printf("size=%d\n",sizeof(set));
	printf("%d\n",set);//有警告
  sigemptyset(&set);printf("%d\n",set);//0
	sigaddset(&set,2);printf("%d\n",set);//+2
	sigaddset(&set,3);printf("%d\n",set);//+4
	sigaddset(&set,7);printf("%d\n",set);//+64
  sigdelset(&set,3);printf("%d\n",set);
  if(sigismember(&set,2) == 1)
	  printf("信号2存在\n");
	else printf("信号2不存在\n");
	return 0;
}

