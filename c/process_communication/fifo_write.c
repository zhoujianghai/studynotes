#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define FIFO_SERVER "/tmp/myfifo"

int main(int argc,char **argv)
{
	int fd;
	char buf_w[100];
	int num_w;

	memset(buf_w,0,sizeof(buf_w));
//创建有名管道
	if(mkfifo(FIFO_SERVER,O_CREAT | O_EXCL | O_RDWR) < 0 && (errno != EEXIST))
	{
		printf("create fifoserver failure\n");
		exit(EXIT_FAILURE);
	}
	//以可读写 不堵塞的方式打开管道,如果errno为13,则没有访问权限
	fd = open(FIFO_SERVER,O_RDWR | O_NONBLOCK,0);
	if(fd == -1)
	{
		printf("open fifoserver failure:%d\n",errno);
		exit(EXIT_FAILURE);
	}

	if(argc == 1)
	{
		printf("please send some texts\n");
		exit(EXIT_FAILURE);
	}
	strcpy(buf_w,argv[1]);
	if((num_w = write(fd,buf_w,100)) == -1)
	{
		if(errno == EAGAIN)
			printf("try again\n");
	}
	else
	{
		printf("write %s to FIFO\n",buf_w);
	}
	close(fd);
	return EXIT_SUCCESS;

}
