#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  pid_t pid = vfork();
  if(!pid){
	  sleep(1);
	  printf("子进程运行\n");//子进程单独运行
	  execl("/bin/ls","ls",NULL);//父子进程并行
	  //printf("子进程结束\n");//无法执行
	  exit(-1);//后面必须写exit(),实现错误时退出
	  /*sleep(3);
	    printf("child runing\n");
	    sleep(1);
	    printf("child over\n");
	    exit(0);*/
  }
 //sleep(1);
  printf("father over\n");
}

