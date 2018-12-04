#include <stdio.h>
#include <unistd.h>
int main (void) {
	printf ("ABC");
	pid_t pid = fork ();
	if (pid == -1) {
		perror ("fork");
		return -1;
	}
	if (pid == 0) {
		printf ("XYZ\n"); // ABCXYZ
		return 0;
	}
	sleep (1);
	printf ("\n"); // ABC
	return 0;
}
