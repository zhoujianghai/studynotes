#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define SERVER_PORT 8888
#define MAX_MSG_LEN 1024

void printf_recv(int sockfd)
{
	struct sockaddr_in addr;
	int addrlen,n;
	char msg[MAX_MSG_LEN];

	while(1)
	{
		bzero(msg,sizeof(msg));
		addrlen = sizeof(struct sockaddr_in);
		n = recvfrom(sockfd,msg,MAX_MSG_LEN,0,(struct sockaddr*)&addr,&addrlen);
		msg[n] = '\0';
		fprintf(stdout,"received msg:%s\n",msg);
	}
}


int main(void)
{
	struct sockaddr_in addr;
	int sockfd;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);
		printf("create socket %d\n",sockfd);
	if(sockfd < 0)
	{
		fprintf(stderr,"create socket error:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}

	int on;
	on = -1;
	//设置socket状态，SO_REUSEADDR允许地址重用,避免出现Address aleardy in use
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

	bzero(&addr,sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(SERVER_PORT);

	if(bind(sockfd,(struct sockaddr*)&addr,sizeof(struct sockaddr_in)) < 0)
	{
		fprintf(stderr,"bind socket error:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf_recv(sockfd);
	close(sockfd);

	return EXIT_SUCCESS;
}
