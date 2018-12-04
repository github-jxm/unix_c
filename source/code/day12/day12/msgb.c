#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
	key_t key = ftok(".",100);
	int msgid = msgget(key,0);
	if(msgid == -1) perror("msgget"),exit(-1);
	char buf[50] = { };
	int res = msgrcv( msgid, buf, sizeof(buf), 0, 
			  IPC_NOWAIT);//IPC_NOWAIT空了不会等待
	if(res == -1) {
		perror("msgsnd");
	}else {
		printf("%s\n",buf);
	}
}
