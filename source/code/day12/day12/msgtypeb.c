#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg{  //名字程序员随便起
  long mtype;//固定的，消息类型
  char name[100];//数据区
};
int main()
{
	key_t key = ftok(".",100);
	int msgid = msgget(key,0);
	if(msgid == -1) perror("msgget"),exit(-1);
	struct msg msg1;
	int res = msgrcv(msgid,&msg1,
			 sizeof(msg1.name),2,0);
	if(res==-1) perror("msgrcv"),exit(-1);
	printf("res=%d,name=%s\n",res,msg1.name);
}
