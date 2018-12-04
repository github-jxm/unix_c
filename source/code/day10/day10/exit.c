#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void fa(){
  printf("fa is called\n");
}
int main(){
  atexit(fa);//退出前调用fa()
	printf("begin\n");
	//exit(0);//调用fa()
	//_Exit(0);//立即退出，不调用fa()
	printf("end\n");
	return 0;//return相当于exit(0)
}

