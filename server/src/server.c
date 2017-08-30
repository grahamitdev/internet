#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/sem.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <pthread.h>
void *th_fn(void *arg)
{
	int clientfd = (int)arg;
	while(1)
	{
		char buffer[1024] = "";
		if(read(clientfd,buffer,1024) <= 0)
		{
			break;
		}
		printf("%s\n",buffer);
	}
	return NULL;
}
int main(void)
{
	//第一步:socket开银行搭建银行文件库
	int serverfd = socket(AF_INET,SOCK_STREAM,0);
	if(serverfd == -1)
	{
		fprintf(stderr,"函数名:%s 行号:%d 错因: %s\n",__func__,__LINE__,strerror(errno));
		exit(EXIT_FAILURE);
	}
	//第二步:PORT、IP 开业务、选址
	struct sockaddr_in s_addr = {};
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(8080);
	if(inet_pton(AF_INET,"192.168.118.138",&s_addr.sin_addr.s_addr) == -1)
	{
		fprintf(stderr,"函数名:%s 行号:%d 错因: %s\n",__func__,__LINE__,strerror(errno));
		exit(EXIT_FAILURE);		
	}
	//第三步:bind银行开门
	if(bind(serverfd,(struct sockaddr *)&s_addr,sizeof(s_addr)) == -1)
	{
		fprintf(stderr,"函数名:%s 行号:%d 错因: %s\n",__func__,__LINE__,strerror(errno));
		exit(EXIT_FAILURE);
	}
	//第四步:listen卖票
	if(listen(serverfd,5) == -1)
	{
		fprintf(stderr,"函数名:%s 行号:%d 错因: %s\n",__func__,__LINE__,strerror(errno));
		exit(EXIT_FAILURE);
	}
	//第五步:accept窗口服务人员叫号
	while(1)
	{
		struct sockaddr_in client_addr;
		socklen_t client_len = sizeof(struct sockaddr_in);
		int clientfd = accept(serverfd,(struct sockaddr *)&client_addr,&client_len);
		if(clientfd == -1)
		{
			fprintf(stderr,"函数名:%s 行号:%d 错因: %s\n",__func__,__LINE__,strerror(errno));
			exit(EXIT_FAILURE);
		}
		char ip_buffer[1024] = "";
		char ip[1024] = "";
		strcpy(ip,inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,ip_buffer,1024));
		printf("IP:%s 连接上了服务器\n",ip);
		//第六步:办业务开辟分布式线程(不需要join),io
		pthread_t pthread;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
		int err = 0;
		if((err = pthread_create(&pthread,&attr,th_fn,(void *)clientfd)) != 0)
		{
			fprintf(stderr,"函数名:%s 行号:%d 错因: %s\n",__func__,__LINE__,strerror(errno));
			exit(EXIT_FAILURE);
		}

		
	}
	//第七步:close 银行倒闭
	return 0;
	


	
}
