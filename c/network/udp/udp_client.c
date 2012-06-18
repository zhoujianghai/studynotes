#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define SERVER_PORT 8888
#define MAX_BUF_SIZE 1024

void udp_send_msg(int sockfd,const struct sockaddr_in *addr,int addrlen)
{
	char buffer[MAX_BUF_SIZE];
	while(1)
	{
		bzero(buffer,MAX_BUF_SIZE);
		printf("please enter char:\n");
		fgets(buffer,MAX_BUF_SIZE,stdin);
		sendto(sockfd,buffer,MAX_BUF_SIZE,0,(struct sockaddr*)addr,addrlen);
		bzero(buffer,MAX_BUF_SIZE);
	}
}

int main(int argc,char **argv)
{
	struct sockaddr_in addr;
	int sockfd,port;

	if(argc < 3)
	{
		fprintf(stderr,"please input ip : %s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	port = atoi(argv[2]);

	sockfd = socket(AF_INET,SOCK_DGRAM,0);
		printf("create socket %d\n",sockfd);
	if(sockfd < 0)
	{
		fprintf(stderr,"create socket error : %s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	bzero(&addr,sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	//inet_aton:将字符串的ip地址转换成网络上的二进制数
	int aton_ret = inet_aton(argv[1],&addr.sin_addr);
	printf("aton_ret:%d\n",aton_ret);
	if(aton_ret < 0)
	{
		fprintf(stderr,"ip error : %s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	udp_send_msg(sockfd,&addr,sizeof(struct sockaddr_in));

	return EXIT_SUCCESS;
}
