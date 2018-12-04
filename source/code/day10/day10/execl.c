#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  printf("begin\n");
	execl("/bin/ls","ls","-l",NULL);
	printf("end\n");//如果execl()失败，继续运行
}

