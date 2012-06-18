#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "msgqueue_common.h"

int main(void)
{
	int running = 1;
	msg_queue msg_queue_content;
	int msgid;
	long rcv_msg_type;
	//创建消息队列
	msgid = msgget((key_t)1234,0666 | IPC_CREAT);
	if(msgid == -1)
	{
		fprintf(stderr,"create msg queue failed:%d\n",errno);	
		exit(EXIT_FAILURE);
	}

	while(running)
	{
		//从指定消息队列中接收消息
		if(msgrcv(msgid,(void *)&msg_queue_content,TEXT_SIZE,rcv_msg_type,0) == -1)	
		{
			fprintf(stderr,"receive msg error:%d\n",errno);
			exit(EXIT_FAILURE);
		}
		printf("you write : %smsg_type:%d\n",msg_queue_content.msg_text,rcv_msg_type);
		
		if(strncmp(msg_queue_content.msg_text,"end",3) == 0)
		{
			running = 0;	
		}
	}
	//msgctl:操纵消息队列，IPC_RMID：从内核中移除指定消息队列
	if(msgctl(msgid,IPC_RMID,0) == -1)
	{
			fprintf(stderr,"remove msgqueue error:%d\n",errno);
			exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
