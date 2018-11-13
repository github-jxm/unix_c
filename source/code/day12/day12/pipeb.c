#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int fd = open("aa",O_RDONLY);
	if(fd == -1) perror("open"),exit(-1);
	while(1){
		int i;
	  int res = read(fd,&i,sizeof(i));
		if(res == 0) break;
    if(res == -1){ perror("read"); break; }
		printf("i=%d\n",i);
	}
	close(fd);
}

