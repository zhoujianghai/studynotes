#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm_com.h"


int main()
{
	int shmid;
	int running = 1;
	//共享内存区对象
	shared_memory *shared_m;
	//共享内存的起始地址
	void *shared_m_first = (void *)0;
//创建共享内存,IPC_CREATE:若没有则创建，否则就打开
	shmid = shmget((key_t)1234,sizeof(shared_memory),0666 | IPC_CREAT);
	if(shmid == -1)
	{
		printf("create shared memory error \n");
		exit(EXIT_FAILURE);
	}
	//共享内存区对象映射到调用进程的地址空间
	shared_m_first = shmat(shmid,(void *)0,0);
	if(shared_m_first == -1)
	{
		fprintf(stderr,"shmat failed \n");
		exit(EXIT_FAILURE);
	}
	printf("Memeory attached at %X\n",(int)shared_m_first);
	shared_m = (shared_memory *)shared_m_first;
	shared_m->write_by_you = 0;
	while(running)
	{
		if(shared_m->write_by_you)
		{
			printf("you are write:%s \n",shared_m->some_text);
			sleep(1);
			shared_m->write_by_you = 0;
			if(strncmp(shared_m->some_text,"end",3) == 0)
			{
				printf("good bye \n");
				running = 0;
			}
		}
	}
	//让进程跟共享内存块脱离
	if(shmdt(shared_m_first) == -1)
	{
		fprintf(stderr,"shmdt failed \n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
