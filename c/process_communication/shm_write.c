#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shm_com.h"


int main()
{
	int shmid;
	int running = 1;
	shared_memory *shared_m;
	void *shared_m_first = (void *)0;
	char buff[BUFSIZ] = {0};

	shmid = shmget((key_t)1234,sizeof(shared_memory),0666 | IPC_CREAT);
	if(shmid == -1)
	{
		fprintf(stderr,"create shared memory error \n");
		exit(EXIT_FAILURE);
	}

	shared_m_first = shmat(shmid,(void *)0,0);
	if(shared_m_first == -1)
	{
		fprintf(stderr,"shmat failed \n");
		exit(EXIT_FAILURE);
	}
	printf("Memory attached at %X\n",(int)shared_m_first);

	shared_m = (shared_memory *)shared_m_first;

	while(running)
	{
		while(shared_m->write_by_you == 1)
		{
			printf("wait for client \n");
			sleep(1);
		}
		memset(buff,0,sizeof(buff));
		printf("enter some texts \n");
		//从标准输入流中读取字符串
		fgets(buff,BUFSIZ,stdin);
		strncpy(shared_m->some_text,buff,TEXT_SIZE);
		shared_m->write_by_you = 1;
		//字符串比较
		if(strncmp(buff,"end",3) == 0)
		{
			running = 0;
		}
	}
	if(shmdt(shared_m_first) == -1)
	{
		fprintf(stderr,"shmdt failed \n");
		exit(EXIT_FAILURE);
	}
	return EXIT_FAILURE;
}
