#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>


int main(int argc,char **argv)
{
	pid_t child;
	child = fork();
	if(child == -1)
	{
	//	printf("fork error : %s\n",strerror(errno));
		exit(1);
	}
	else if(child == 0)
	{
		printf("I am a child:%d\n",getpid());
		exit(0);
	}
	else if(child > 0)//equal the child process id
	{
		printf("I am father:%d\n",getpid());
		return 0;
	}
}
