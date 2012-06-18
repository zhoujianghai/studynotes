#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *thread(void *arg)
{
	int i;
	for(i = 0; i < 3; ++i)
	{
		sleep(2);
		printf("thread i:%d\n",i);
	}
	 return NULL;
}

int main(void)
{
	pthread_t pt;
	int error;

	error = pthread_create(&pt,NULL,thread,NULL);
	if(error)
	{
		printf("create thread error\n");
		exit(EXIT_FAILURE);
	}

	printf("process will be block\n");
	pthread_join(pt,NULL);
	int i;
	for(i = 0; i < 2; ++i)
	{
		printf("process i : %d\n",i);	
	}

	return EXIT_SUCCESS;
}
