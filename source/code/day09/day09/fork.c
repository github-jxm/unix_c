#include <stdio.h>
#include <unistd.h>
void run (char c) 
{
	size_t i;
	for (i = 0; i < 100; ++i) {
		printf ("%c", c);
		usleep (100000);
	}
}
int main (void) 
{
	setbuf (stdout, NULL);
	/*
	printf ("%d进程：我要调用fork了...\n", getpid ());
	pid_t pid = fork ();
	if (pid == -1) {
		perror ("fork");
		return -1;
	}
	if (pid == 0) {
		printf ("%d进程：我是%d进程的子进程。\n", getpid (), getppid ());
		run ('-');
		return 0;
	}
	pid = fork ();
	if (pid == 0) {
		run ('X');
		return 0;
	}
	pid = fork ();
	if (pid == 0) {
		run ('#');
		return 0;
	}
	printf ("%d进程：我是%d进程的父进程。\n",
		getpid (), pid);
	run ('+');
	sleep (1);
	*/
	int i;
	for (i = 0; i < 10; ++i) {
		pid_t pid = fork ();
		if (pid == 0) {
			run ('A'+i);
			return 0;
		}
	}
	return 0;
}
