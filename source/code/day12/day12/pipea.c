#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
  //int fd=open("aa",O_RDWR);//权限不能是读写
	int fd = open("aa",O_WRONLY);
	if(fd == -1) perror("open"),exit(-1);
  int i;
	for(i=0;i<100;i++){
	  write(fd,&i,sizeof(i));
		usleep(100000);//休眠0.1秒
	}
	close(fd);
  printf("write over\n");
}

