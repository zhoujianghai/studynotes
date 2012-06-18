#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pid_t child;
	child = vfork();
	if(child == -1) exit(1);
	else if(child == 0)
	{
		sleep(2);
		printf("I am a child : %d\n",getpid());
		exit(0);
	}
	else
	{
		printf("I am a father: %d\n",getpid());
		return 0;
	}
}
