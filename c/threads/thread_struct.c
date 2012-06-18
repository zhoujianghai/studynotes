#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
//创建一个线程，并执行，并向线程执行的函数传递一个结构体。ps：编译的时候需要加-lpthread
typedef struct
{
	int id;
	char *name;
}student_info;

void *create(void *arg)
{
	student_info *si = (student_info *)arg;	
	printf("id:%d\n",si->id);
	printf("name:%s\n",si->name);
	return (void *)0;
}

int main(void)
{
	student_info *si;
	//为结构体分配内存
	si = (student_info *)malloc(sizeof(student_info));
	pthread_t pt;
	int error;

	si->id = 30;
	si->name = "zhoujianghai";

	error = pthread_create(&pt,NULL,create,(void *)si);

	if(error)
	{
		printf("create thread error\n");
		exit(EXIT_FAILURE);
	}

	sleep(1);

	return EXIT_SUCCESS;

}
