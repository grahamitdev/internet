#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>

//第一步:socket用户文件库

//第二步:connect


int main(void)
{
	int clientfd = socket(AF_INET,SOCK_STREAM,0);
	if(clientfd == -1)
	{
		fprintf(stderr,"函数名:%s 行号:%d 错因:%s\n",__func__,__LINE__,strerror(errno));
		exit(EXIT_FAILURE);
	}
	struct sockaddr_in s_addr;
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(8080);
	if(inet_pton(AF_INET,"192.168.31.175",&s_addr.sin_addr.s_addr) == -1)
	{
		fprintf(stderr,"函数名:%s 行号:%d 错因:%s\n",__func__,__LINE__,strerror(errno));
		exit(EXIT_FAILURE);
	}
	if(connect(clientfd,(struct sockaddr *)&s_addr,sizeof(struct sockaddr)) == -1)
	{
		fprintf(stderr,"函数名:%s 行号:%d 错因:%s\n",__func__,__LINE__,strerror(errno));
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		char buffer[1024] = "";
		printf("请输入:");
		scanf("%s",buffer);
		if(write(clientfd,buffer,strlen(buffer)) <= 0)
		{
			fprintf(stderr,"函数名:%s 行号:%d 错因:%s\n",__func__,__LINE__,strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	close(clientfd);

	return 0;
}
