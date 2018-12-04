#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int global = 10; // 全局变量，数据区
int main (void) 
{
	int local = 20; // 局部变量，栈区
	int* heap = malloc (sizeof (int)); // 堆区
	*heap = 30;
	printf ("父进程：%d %d %d\n", global, local, *heap); // 10 20 30
	pid_t pid = fork ();
	if (pid == -1) {
		perror ("fork");
		return -1;
	}
	if (pid == 0) {
		printf ("子进程：%d %d %d\n", ++global, ++local, ++*heap); // 11 21 31
		free (heap);
	}else {
		sleep (1);
		printf ("父进程：%d %d %d\n", global, local, *heap); // 10 20 30
		free (heap);
	}
	return 0;
}
