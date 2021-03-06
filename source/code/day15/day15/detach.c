/*
 * detach.c
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void* thread_proc (void* arg) {
	//pthread_detach (pthread_self ());
	int i;
	for (i = 0; i < 200; ++i) {
		putchar ('-');
		usleep (50000);
	}
	return NULL;
}
int main (void) {
	setbuf (stdout, NULL);
	pthread_t tid;
	pthread_create (&tid, NULL, thread_proc, NULL);
	pthread_detach (tid);
	int error = pthread_join (tid, NULL);
	if (error){
		printf ("pthread_join: %s\n", strerror (error));
	}
	int i;
	for (i = 0; i < 200; ++i) {
		putchar ('+');
		usleep (50000);
	}
	printf ("\n");
	return 0;
}
