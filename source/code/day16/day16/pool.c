#include <stdio.h>
#include <string.h>
#include <pthread.h>
int g_pool = 0;
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
void* pool1 (void* arg) {
	unsigned int i;
	pthread_mutex_lock (&g_mutex);
	for (i = 0; i < 100000000; ++i) {
	//	pthread_mutex_lock (&g_mutex);
		++g_pool;
	//	pthread_mutex_unlock (&g_mutex);
	}
	pthread_mutex_unlock (&g_mutex);
	return NULL;
}
void* pool2 (void* arg) {
	unsigned int i;
	pthread_mutex_lock (&g_mutex);
	for (i = 0; i < 100000000; ++i) {
	//	pthread_mutex_lock (&g_mutex);
		--g_pool;
	//	pthread_mutex_unlock (&g_mutex);
	}
	pthread_mutex_unlock (&g_mutex);
	return NULL;
}
int main (void) {
	//pthread_mutex_init (&g_mutex, NULL);
	pthread_t tid1;
	pthread_create (&tid1, NULL, pool1, NULL);
	pthread_t tid2;
	pthread_create (&tid2, NULL, pool2, NULL);
	pthread_join (tid1, NULL);
	pthread_join (tid2, NULL);
	printf ("%u\n", g_pool);
	//pthread_mutex_destroy (&g_mutex);
	return 0;
}
