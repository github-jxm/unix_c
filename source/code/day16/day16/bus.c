/*
 * bus.c
 */

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int g_cn = 5; // 空座位
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t g_sem;

// 乘客线程
void* thread_proc (void* arg) {
	sem_wait (&g_sem);
	pthread_mutex_lock (&g_mutex);
	printf ("%lu坐下，还剩%d个空座。\n", pthread_self (), --g_cn);
	pthread_mutex_unlock (&g_mutex);
	usleep (50000); // 坐车时间
	pthread_mutex_lock (&g_mutex);
	printf ("%lu下车，还剩%d个空座。\n", pthread_self (), ++g_cn);
	pthread_mutex_unlock (&g_mutex);
	sem_post (&g_sem);
	return NULL;
}
int main (void) {
	sem_init (&g_sem, 0, g_cn);
	printf ("发车时共有%d个空座。\n", g_cn);
	pthread_t tids[20];
	int i;
	for (i = 0; i < 20; ++i){
		pthread_create (&tids[i], NULL, thread_proc, NULL);
	}

	for (i = 0; i < 20; ++i){
		pthread_join (tids[i], NULL);
	}
	printf ("收车时共有%d个空座。\n", g_cn);
	sem_destroy (&g_sem);
	return 0;
}
