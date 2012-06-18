#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define portnumber 6666

int main(void)
{
	int sockfd,clientfd;
	struct sockaddr_in server_info;
	struct sockaddr_in client_info;
	int sin_size;
	int newbytes;
	char buffer[1024];
	//AF_INET:Address Family,ipv4网络协议，SOCK_STREAM:面向链接的稳定数据传输，TCP协议,0:传输协议编号
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		fprintf(stderr,"create socket error:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}

	int on;
	on = -1;
	//设置socket状态，SO_REUSEADDR允许地址重用,避免出现Address aleardy in use
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	bzero(&server_info,sizeof(struct sockaddr_in));
	server_info.sin_family = AF_INET;
	//htonl:将本机上的long数据转换为网络上的long数据,INADDR_ANY:服务器可以绑定到主机任何 ip,sin_addr是struct in_addr,表示一个32位的ip地址
	server_info.sin_addr.s_addr = htonl(INADDR_ANY);
	server_info.sin_port = htons(portnumber);
	//捆绑sockfd描述符到ip地址
	if(bind(sockfd,(struct sockaddr_in *)(&server_info),sizeof(struct sockaddr_in)) == -1)
	{
		fprintf(stderr,"bind socket error:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	//设置允许链接的最大客户端数
	if(listen(sockfd,5) == -1)
	{
		fprintf(stderr,"listen socket error:%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		sin_size = sizeof(struct sockaddr_in);
		//服务端堵塞，直到客户端建立 链接,第二个参数是远程主机的地址信息
		if((clientfd = accept(sockfd,(struct sockaddr_in *)(&client_info),&sin_size)) == -1)
		{
				fprintf(stderr,"accept client connect  error:%s\n",strerror(errno));
				exit(EXIT_FAILURE);
		}
		//inet_ntoa:将网络二进制数字转换成网络地址字符串,必须加上arpa/inet.h,否则使用inet_ntop
		fprintf(stderr,"get connection from %s\n",inet_ntoa(client_info.sin_addr));

		if((newbytes = read(clientfd,buffer,1024)) == -1)
		{
				fprintf(stderr,"read data  error:%s\n",strerror(errno));
				exit(EXIT_FAILURE);
		}

		buffer[newbytes] = '\0';
		printf("read data:%s\n",buffer);
		close(clientfd);
	}

	close(sockfd);
	return EXIT_SUCCESS;

}
