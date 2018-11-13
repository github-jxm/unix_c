/*
 * exit.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define PI 3.1415926

void* area (void* arg) {
	double r = *(double*)arg;
	double* s = malloc (sizeof (double));
	*s = 2 * PI * r;
	pthread_exit (s);
	*s = PI * r * r;
	return s;
}
int main (void) {
	//pthread_exit (NULL);
	double r = 10;
	pthread_t tid;
	pthread_create (&tid, NULL, area, &r);
	double* s;
	pthread_join (tid, (void**)&s); // *s = ...
	printf ("%g\n", *s);
	free (s);
	return 0;
}
