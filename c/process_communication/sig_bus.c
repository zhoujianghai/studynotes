#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void my_func(int sign_no)
	{
		if(sign_no == SIGBUS)
			printf("I have got a sigbus\n");
	}

int main()
{

	printf("wait sigbus \n");
	signal(SIGBUS,my_func);

	pause();
	return EXIT_FAILURE;
}
