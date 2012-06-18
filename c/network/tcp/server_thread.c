#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <netinet/in.h>
#include <signal.h>

#define SERVER_PORT 8888

void *th_func(void *arg)
{
	int *com_fd_p = (int *)arg;
	int com_fd = *com_fd_p;
	char recv_buf[1024];
	int size,j;
	printf("com_fd=%d\n",com_fd);
	memset(&recv_buf,0,sizeof(recv_buf));
	while((size = read(com_fd,recv_buf,1024)) > 0)
	{
		if(recv_buf[0] == '@')
		  break;

		printf("message from client(%d):%s\n",size,recv_buf);
		//将客户端发送过来的信息转换成大写，并发送给客户端
		int i;
		for(i = 0; i < size; i++)
		  recv_buf[i] = toupper(recv_buf[i]);

		write(com_fd,recv_buf,size);
	}
	close(com_fd);
	return 0;
}

int main(void)
{
  	socklen_t client_addr_len;
	int listen_fd;
	int com_fd;
	int ret,i,len;
	char recv_buf[1024];
	pthread_t tid;

	struct sockaddr_in client_addr;
	struct sockaddr_in server_addr;
//创建socket,PE_INET:Protocol Family,AF_INET:Address Family,创建socket时是指定协议，应该用PF	
	listen_fd = socket(PF_INET,SOCK_STREAM,0);
	if(listen_fd < 0)
	{
		perror("cannot create listen socket!");
		exit(EXIT_FAILURE);
	}
	//填充服务器的套接字信息
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_PORT);
//将服务器和套接字绑定
	ret = bind(listen_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(ret == -1)
	{
		perror("cannot bind server socket!");
		close(listen_fd);
		exit(EXIT_FAILURE);
	}
	//接听指定端口，连接5个客户端
	ret = listen(listen_fd,5);
	if(ret == -1)
	{
		perror("cannot listen the client connect request!");
		close(listen_fd);
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		len = sizeof(client_addr);	
		com_fd = accept(listen_fd,(struct sockaddr*)&client_addr,&len);

		if(com_fd < 0)
		{
		  if(errno == EINTR)
			continue;
		  else
		  {
			perror("cannot accept client connect request!");
			close(listen_fd);
			exit(EXIT_FAILURE);
		  }
		}
		
		printf("com_fd=%d\n",com_fd);
		//对每个连接的客户端创建一个线程
		if((pthread_create(&tid,NULL,th_func,&com_fd)) == -1)
		{
			perror("create thread error!");
			close(listen_fd);
			close(com_fd);
			exit(EXIT_FAILURE);
		}
	}

	return EXIT_SUCCESS;
}
