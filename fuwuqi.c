#include "ls.h"
main()
{
	int       sock_fd,conn_fd,sleep_fd=0;
	int       optval;
	int       flag_recv = USERNAME;
	int       ret;
	int       name_num;
	pthread_t thid,sleepthidt;
	pid_t     pid;
	socklen_t cli_len;
	struct sockaddr_in  serv_addr,cli_addr;
	char      recv_buf[128]; 
	char      recv_msg[200];
	char	  exit_msg[]="/quit";
	
	printf("创建套接字");
	my_sleep();
	//IPv4   TCP流 
	sock_fd = socket(AF_INET,SOCK_STREAM,0);
	if(sock_fd<0)
		my_err("创建套接字失败",__LINE__);
	printf("创建套接字成功!\n");
	sleep(1);
	
	printf("套接字属性设置");
	my_sleep();
	printf("设置套接字可以重新绑定端口");
	my_sleep();
	optval = 1;
	if(setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int))<0)
		my_err("设置套接字可以重新绑定窗口失败！\n",__LINE__);
	printf("设置套接字属性成功！\n");
	sleep(1);

	printf("初始化服务器地址结构");
	my_sleep();
	memset(&serv_addr,0,sizeof(struct sockaddr_in));
	// TCP/IP协议
	serv_addr.sin_family = AF_INET;
	//  端口号 宏定义
	serv_addr.sin_port =htons(SERV_PORT);
	//所有任何网络接口
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	printf("初始化服务器地址完成！\n");
	sleep(1);

	printf("绑定套接字到本地端口");
	my_sleep();
	if(bind(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in))<0)
		my_err("绑定套接字失败！",__LINE__);
	printf("绑定套接字成功！\n");
	sleep(1);


	printf("将套接字转换为监听模式");
	my_sleep();
	if(listen(sock_fd,LISTENQ)<0)
		my_err("转换为监听模式失败！",__LINE__);
	printf("转换为监听模式成功！\n");
	sleep(1);

	cli_len=sizeof(struct sockaddr_in);

	printf("等待客户连接中");
	fflush(stdout);
	pthread_create(&sleepthidt,NULL,sleepthid,&sleep_fd);
	conn_fd = accept(sock_fd,(struct sockaddr *)&cli_addr,&cli_len);
	if(conn_fd<0)
		my_err("链接出错！\n",__LINE__);
	sleep_fd=1;
	sleep(1);
	printf("\n");
	printf("接收到新的客户端，IP为：%s\n",inet_ntoa(cli_addr.sin_addr));
	
	pthread_create(&thid,NULL,send_data,&conn_fd);
	while(1)
	{
		if (recv(conn_fd,recv_msg,sizeof(recv_msg),0) == -1) 
		{
			perror("接收数据出错");
			exit(1);
		}

		if (!strcmp(recv_msg,exit_msg)) 
		{
			if (send(conn_fd,exit_msg,sizeof(exit_msg),0) == -1) 
			{
				perror("发送退出消息出错");
				exit(1);
			}
			close(sock_fd);
			close(conn_fd);
			exit(0);
		}


		printf("用户说：%s\n",recv_msg);

	}
	
			
	
		

}

