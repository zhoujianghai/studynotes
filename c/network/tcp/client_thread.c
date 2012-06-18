#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define SERVER_PORT 8888
#define SERVER_IP "127.0.0.1"

int main(void)
{
	int connect_fd,i,ret,len;
	char send_buf[1024];

	struct sockaddr_in server_addr;
	
	connect_fd = socket(PF_INET,SOCK_STREAM,0);
	if(connect_fd < 0)
	{
		perror("cannot create socket!");
		exit(EXIT_FAILURE);
	}

	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	server_addr.sin_port = htons(SERVER_PORT);
	ret = connect(connect_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(ret == -1)
	{
		perror("cannot create socket!");
		close(connect_fd);
		exit(EXIT_FAILURE);
	}
	memset(send_buf,0,1024);
	while(1)
	{
	write(STDOUT_FILENO,"input message:",14);
	len = read(STDIN_FILENO,send_buf,1024);
	if(len > 0)
	{
		write(connect_fd,send_buf,len);
	}

	len = read(connect_fd,send_buf,len);

	if(len > 0)
	  printf("message from server:%s\n",send_buf);
	if(send_buf[0] == '@')
	  break;
	}
	close(connect_fd);
	return EXIT_SUCCESS;
}
