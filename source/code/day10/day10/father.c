#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  pid_t pid = vfork();
	if(pid == 0){
		printf("cpid1=%d\n",getpid());
		execl("./child","child",NULL);//父子并行
	  exit(-1);
	}
  printf("father over\n");
}


