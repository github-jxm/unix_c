/*
 * dead.c
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t g_a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_b = PTHREAD_MUTEX_INITIALIZER;
void* thread1 (void* arg) {
	pthread_t tid = pthread_self ();
	printf ("%lu线程：等待A...\n", tid);
	pthread_mutex_lock (&g_a);
	printf ("%lu线程：获得A！\n", tid);
	sleep (1);
	printf ("%lu线程：等待B...\n", tid);
	pthread_mutex_lock (&g_b);
	printf ("%lu线程：获得B！\n", tid);
	// ...
	pthread_mutex_unlock (&g_b);
	printf ("%lu线程：释放B。\n", tid);
	pthread_mutex_unlock (&g_a);
	printf ("%lu线程：释放A。\n", tid);
	return NULL;
}
void* thread2 (void* arg) {
	pthread_t tid = pthread_self ();
	printf ("%lu线程：等待B...\n", tid);
	pthread_mutex_lock (&g_b);
	printf ("%lu线程：获得B！\n", tid);
	sleep (1);
	printf ("%lu线程：等待A...\n", tid);
	pthread_mutex_lock (&g_a);
	printf ("%lu线程：获得A！\n", tid);
	// ...
	pthread_mutex_unlock (&g_a);
	printf ("%lu线程：释放A。\n", tid);
	pthread_mutex_unlock (&g_b);
	printf ("%lu线程：释放B。\n", tid);
	return NULL;
}
int main (void) {
	pthread_t tid1;
	pthread_create (&tid1, NULL, thread1, NULL);
	pthread_t tid2;
	pthread_create (&tid2, NULL, thread2, NULL);
	pthread_join (tid1, NULL);
	pthread_join (tid2, NULL);
	return 0;
}
