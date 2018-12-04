#include <stdio.h>
#include <unistd.h>
int main (void) {
	printf ("%d进程：我要调用fork了...\n",
		getpid ());
	pid_t pid = fork ();
	if (pid == -1) {
		perror ("fork");
		return -1;
	}
	if (pid == 0) {
		sleep (1);
		printf ("%d进程：我是被%d进程收养的"
			"孤儿进程。", getpid (), getppid ());
		return 0;
	}
	printf ("%d进程：我是%d进程的父进程。"
		"马上就死！\n", getpid (), pid);
	return 0;
}
