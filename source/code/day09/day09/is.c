#include <stdio.h>
#include <unistd.h>
int main (void) {
	printf ("父进程：");
	int a, b, c;
	scanf ("%d%d%d", &a, &b, &c);
	pid_t pid = fork ();
	if (pid == -1) {
		perror ("fork");
		return -1;
	}
	if (pid == 0) {
		int x, y, z;
		scanf ("%d%d%d", &x, &y, &z);
		printf ("子进程：%d %d %d\n", x, y, z);
	}
	else {
		sleep (1);
		printf ("父进程：%d %d %d\n", a, b, c);
	}
	return 0;
}
