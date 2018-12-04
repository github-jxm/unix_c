#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
	key_t key = ftok(".",100);//确保文件存在 1
	int shmid = shmget(key,4,IPC_CREAT|0666);//2
	if(shmid == -1) perror("shmget"),exit(-1);
	int* pi = shmat(shmid,0,0);//3
	*pi = 100;//4
	shmdt(pi);//5 
}//练习：写shmb.c,把100从共享内存读出来并打印

