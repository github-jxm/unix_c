#include <stdio.h>
#include <unistd.h>
int main (void) {
	printf ("    进程ID：%d\n", getpid ());
	printf ("  父进程ID：%d\n", getppid ());
	printf ("实际用户ID：%d\n", getuid ());
	printf ("  实际组ID：%d\n", getgid ());
	printf ("有效用户ID：%d\n", geteuid ());
	printf ("  有效组ID：%d\n", getegid ());
	return 0;
}
