#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

//the father run until child exit
int main(void)
{
	pid_t child;
	child = fork();

	if(child == -1)
	{
		printf("error!!");
		return EXIT_FAILURE;
	}
	else if(child == 0)
	{
		printf("child sleep::");
		sleep(2);
		printf("child run:%d\n",getpid());
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("father wait");
		wait(NULL);
		printf("father run:%d\n",getpid());
		return EXIT_SUCCESS;
	}
}
