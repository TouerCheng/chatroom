#include "ls.h"
int main(int argc,char *argv[])
{
	int    	      i;
	int    	    ret;
	int 	conn_fd;
	int   serv_port;
	struct  sockaddr_in serv_addr;
	char    recv_buf[BUFSIZE];
	pthread_t thid;
	char exit_msg[]="/quit";
	char recve_msg[200];

	printf("初始化服务器地址结构......\n");
	memset(&serv_addr,0,sizeof(struct sockaddr_in));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERV_PORT);
	if(inet_aton(argv[1],&serv_addr.sin_addr)<0)
		my_err("初始化服务器地址结构失败！",__LINE__);
	printf("初始化服务器地址结构成功!");
	
	printf("创建一个套接字......\n");
	conn_fd = socket(AF_INET,SOCK_STREAM,0);
	if(conn_fd<0)
		my_err("创建套接字失败",__LINE__);
	printf("创建套接字成功！");

	printf("向服务器发送连接请求.....\n");
	if(connect(conn_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr))<0)
		my_err("发送链接失败！",__LINE__);
	printf("建立连接成功！\n");
	
	/*if (connect(conn_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in))<0) 
	{
		perror("服务器连接失败");
		exit(1);
	}*/
	printf("服务器连接成功.\n");

	pthread_create(&thid,NULL,send_data,&conn_fd);
	
	while (1) 
	{

		if (recv(conn_fd,recve_msg,sizeof(recve_msg),0) == -1) 
		{
			perror("接收数据出错");
			exit(1);
		}

		if (!strcmp(recve_msg,"/quit")) 
		{
			if (send(conn_fd,exit_msg,sizeof(exit_msg),0) == -1) 
			{
				perror("发送退出消息出错");
				exit(1);
			}
			close(conn_fd);
			exit(0);
		}
		
		printf("主机说：%s\n",recve_msg);
	
	}
	return 0;
}
