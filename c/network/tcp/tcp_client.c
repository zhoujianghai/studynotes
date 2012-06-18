#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define portnumber 6666

int main(int argc,char **argv)
{
	int sock_fd;
	char buffer[1024];
	struct sockaddr_in server_info;
	//记录主机的信息：主机名，地址列表等等
	struct hostent *host;

	if(argc != 2)
	{
		printf("please enter ip address \n");
		exit(EXIT_FAILURE);
	}

	if((host = gethostbyname(argv[1])) == NULL)
	{
		fprintf(stderr,"get hostname error\n");	
		exit(EXIT_FAILURE);
	}

	if((sock_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		fprintf(stderr,"create socket error:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}

	bzero(&server_info,sizeof(struct sockaddr_in));
	server_info.sin_family = AF_INET;
	server_info.sin_port = htons(portnumber);
	//ip地址
	server_info.sin_addr = *(struct in_addr *)host->h_addr;

	if(connect(sock_fd,(struct sockaddr_in *)&server_info,sizeof(struct sockaddr_in)) == -1)
	{
		fprintf(stderr,"connect server error:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("connect success,please input data:\n");
	fgets(buffer,1024,stdin);
	write(sock_fd,buffer,strlen(buffer));

	close(sock_fd);
	exit(EXIT_FAILURE);
}

