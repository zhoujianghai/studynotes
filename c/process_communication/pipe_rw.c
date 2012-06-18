#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int pipe_fd[2];
	char buf_r[100];
	pid_t pid;
	int r_num;

	memset(buf_r,0,sizeof(buf_r));
	//create pipe
	if(pipe(pipe_fd) < 0)
	{
		printf("create pipe error\n");
		return EXIT_FAILURE;
	}
//create child process
	if((pid = fork()) == -1)
	{
		printf("create process error \n");
		return EXIT_FAILURE;
	}
	else if(pid == 0)
	{
		//close the write for pipe
		close(pipe_fd[1]);
		//in order to parent process have enough time to write data to pipe
		sleep(2);
		if(r_num = read(pipe_fd[0],buf_r,100) > 0)
		{
			printf("%d numbers read from pipe is %s\n",r_num,buf_r);
		}
		//close the read for pipe
		close(pipe_fd[0]);
		exit(EXIT_SUCCESS);
	}
	else if(pid > 0)
	{
		close(pipe_fd[0]);
		if(write(pipe_fd[1],"hello",5) != -1)
		{
			printf("wirte 1:hello\n");
		}
		if(write(pipe_fd[1],",alex",5) != -1)
		{
			printf("write 2:,alex\n");
		}
		close(pipe_fd[1]);
		//wait the pid process exit
		waitpid(pid,NULL,0);
		exit(EXIT_SUCCESS);
	}

	return EXIT_SUCCESS;
}
