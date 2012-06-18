#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FIFO "/tmp/myfifo"

int main()
{
	char buf_r[100];
	int fd;
	int num_r;

	memset(buf_r,0,sizeof(buf_r));

	fd = open(FIFO,O_RDONLY | O_NONBLOCK,0);

	if(fd == -1)
	{
		printf("open fifo error\n");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		memset(buf_r,0,sizeof(buf_r));
		if((num_r = read(fd,buf_r,100)) == -1)
		{
			if(errno == EAGAIN)
			printf("no data yet \n");
		}
			printf("read data:%s \n",buf_r);
			sleep(1);
	}

	close(fd);
	pause();
	unlink(FIFO);
	return EXIT_SUCCESS;
}

