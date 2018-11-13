/*
 * join.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define PI 3.1415926

double g_s;
void* area (void* arg) {
	double r = *(double*)arg;
	/*
	static double s;
	s = PI * r * r;
	return &s;
	*//*
	double* s = malloc (sizeof (double));
	*s = PI * r * r;
	return s;
	*/
	g_s = PI * r * r;
	return NULL;
}
int main (void) {
	double r = 10;
	pthread_t tid;
	pthread_create (&tid, NULL, area, &r);
	/*
	double* s;
	pthread_join (tid, (void**)&s); // *s = ...
	printf ("%g\n", *s);
	free (s);
	*/
	//sleep (1);
	pthread_join (tid, NULL);
	printf ("%g\n", g_s);
	return 0;
}
