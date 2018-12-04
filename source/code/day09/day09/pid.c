#include <stdio.h>
#include <unistd.h>
int main (void) {
	pid_t pid = getpid ();
	printf ("进程标识：%d\n", pid);
	return 0;
}
