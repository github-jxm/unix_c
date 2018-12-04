#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid1,pid2;
	pid1 = fork();
	if(pid1>0) pid2 = fork();
	if(pid1 == 0){//子进程PID1
		printf("pid1=%d\n",getpid());
		sleep(1); printf("pid1 over\n");
		exit(100); }
	if(pid2 == 0){//子进程PID2
		printf("pid2=%d\n",getpid());
		sleep(3); printf("pid2 over\n");
		exit(200); }
	int sta;
	pid_t pid = waitpid(/*pid2*/-1,&sta,0);
	if(WIFEXITED(sta)){
		printf("pid=%d,sta=%d\n",pid,
		       WEXITSTATUS(sta));
	}
}

