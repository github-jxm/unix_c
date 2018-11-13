#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
struct msg{//名字程序员随便起
  long mtype;//固定的，消息类型
	char name[100];//数据区
};
int main(){
  key_t key = ftok(".",100);
	int msgid = msgget(key,0666|IPC_CREAT);
	if(msgid == -1) perror("msgget"),exit(-1);
  struct msg msg1,msg2;
	msg1.mtype = 1;strcpy(msg1.name,"zhangfei");
  msgsnd(msgid,&msg1,sizeof(msg1.name),0);
	msg2.mtype = 2;strcpy(msg2.name,"guanyu");
  msgsnd(msgid,&msg2,sizeof(msg2.name),0);
}//练习：写msgtypeb.c,用消息类型取出所有的关羽
//并打印

