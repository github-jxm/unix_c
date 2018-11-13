/*
 * create.c
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
void* thread_proc (void* arg) {
	for (;;) {
		printf ("%c", (char)arg);
		usleep (100000);
	}
	return NULL;
}
int main (void) {
	setbuf (stdout, NULL);
	pthread_t tid;
	int error = pthread_create (&tid, NULL, thread_proc, (void*)'A');
	if (error) {
		printf ("pthread_create: %s\n", strerror (error));
		return -1;
	}
	printf ("线程ID：%lu\n", tid);
	error = pthread_create (&tid, NULL, thread_proc, (void*)'B');
	if (error) {
		printf ("pthread_create: %s\n", strerror (error));
		return -1;
	}
	printf ("线程ID：%lu\n", tid);
	thread_proc ((void*)'C');
	//getchar ();
	return 0;
}
