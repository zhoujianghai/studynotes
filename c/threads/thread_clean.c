#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void *clean(void *arg)
{
	char *c = (char *)arg;
	printf("clean:%s\n",c);
	return (void *)0;
}

void *thread1(void *arg)
{
	printf("thead1 start \n");
	pthread_cleanup_push((void *)clean,"thread1 first push");
	pthread_cleanup_push((void *)clean,"thread1 second push");
	printf("thread1 push finish \n");
	if(arg)
	{
			//此处使用return，所以不会执行clean
		return (void *)1;	
	}

	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return (void *)1;
}

void *thread2(void *arg)
{
	printf("thead2 start \n");
	pthread_cleanup_push((void *)clean,"thread2 first push");
	pthread_cleanup_push((void *)clean,"thread2 second push");
	printf("thread2 push finish \n");
	if(arg)
	{
			//此处使用exit，所以会执行clean
			pthread_exit((void *)1);
	}

	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit((void *)1);
}

int main(void)
{
	pthread_t pt1,pt2;
	int err;
	void *ret;

	err = pthread_create(&pt1,NULL,thread1,(void *)1);
	if(err)
	{
		printf("create thread1 error");
		exit(EXIT_FAILURE);
	}
	
	err = pthread_create(&pt2,NULL,thread2,(void *)1);
	if(err)
	{
		printf("create thread2 error");
		exit(EXIT_FAILURE);
	}

	err = pthread_join(pt1,&ret);
	if(err)
	{
		printf("join thread1 error");
		exit(EXIT_FAILURE);
	}
	printf("thread1 exit code %d\n",(int)ret);
	err = pthread_join(pt2,&ret);
	if(err)
	{
		printf("join thread2 error");
		exit(EXIT_FAILURE);
	}
	printf("thread2 exit code %d\n",(int)ret);

	return EXIT_SUCCESS;
}
