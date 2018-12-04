#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid = fork();
	if(pid == -1) perror("fork"),exit(-1);
	if(pid == 0){
		printf("cpid=%d\n",getpid());
		sleep(3);
		printf("child over\n");
		exit(100);
	}
	int sta;
	pid_t wpid = wait(&sta);//取回多种信息
	if(WIFEXITED(sta)){//判断是否正常结束
		printf("exitcode=%d,wpid=%d\n",
			WEXITSTATUS(sta),wpid);//用宏取退出码
	}
	printf("father over\n");
}

