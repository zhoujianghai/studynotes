#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "msgqueue_common.h"


int main(void)
{
	int running = 1;
	msg_queue msg_queue_content;
	int msgid;
	char buf[TEXT_SIZE];
	
	memset(buf,0,sizeof(buf));
	msgid = msgget((key_t)1234,0666 | IPC_CREAT);
	if(msgid == -1)
	{
		fprintf(stderr,"create msgqueue error:%d\n",errno);
		exit(EXIT_FAILURE);
	}

	while(running)
	{
		printf("please enter some texts \n");
		fgets(buf,TEXT_SIZE,stdin);
		msg_queue_content.msg_type = 1;
		strcpy(msg_queue_content.msg_text,buf);
		if(msgsnd(msgid,(void *)&msg_queue_content,TEXT_SIZE,0) == -1)
		{
			fprintf(stderr,"send msg error:%d\n",errno);
			exit(EXIT_FAILURE);
		}
		if(strncmp(buf,"end",3) == 0)
		{
			running = 0;	
		}
		memset(buf,0,sizeof(buf));
	}
	return EXIT_SUCCESS;
	
}
