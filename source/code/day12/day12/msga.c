#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
	key_t key = ftok(".",100);
	int msgid = msgget(key,0666|IPC_CREAT);
	if(msgid == -1) perror("msgget"),exit(-1);

	int res = msgsnd(msgid,"hello",5,0);//IPC_NOWAIT满了不会等待
	if(res == -1) {
		perror("msgsnd"); 
	} else {
		printf("send ok\n");
	}
}//练习：写msgb.c，从队列中读出hello并打印

