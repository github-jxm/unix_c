#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
int main (void) {
	int fd = open ("ftab.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		perror ("open");
		return -1;
	}
	char const* text = "Hello, World !";
	if (write (fd, text, strlen (text)) == -1) {
		perror ("write");
		return -1;
	}
	pid_t pid = fork ();
	if (pid == -1) {
		perror ("fork");
		return -1;
	}
	if (pid == 0) {
		if (lseek (fd, -7, SEEK_CUR) == -1) {
			perror ("lseek");
			return -1;
		}
		close (fd);
		return 0;
	}
	sleep (1);
	text = "Linux";
	if (write (fd, text, strlen (text)) == -1) {
		perror ("write");
		return -1;
	}
	close (fd);
	return 0;
}
