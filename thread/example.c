/*
 * Simple Pthreads example
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *ThreadFunc (void *arg);

int 
main(int argc, char *argv[])
{
	pthread_t idThread;

	puts("let's create a thread!");
	pthread_create(&idThread, NULL, ThreadFunc, (void *) 5);
	pthread_join(idThread, NULL);
}

void *ThreadFunc(void *arg)
{
	int i, n;

	// get the value of the argument passedin
	n = (int) arg;
	
	// do stuff
	for (i = 0; i < n; i++)
		printf("Loop %d: la la la\n", i + 1);
	return NULL;
}
