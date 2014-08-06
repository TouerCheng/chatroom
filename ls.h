#ifndef LS_H
#define LS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
//服务器端的端口
#define SERV_PORT  4500
//链接请求队列最大长度
#define LISTENQ   12

//用户信息无效
#define INVALID_USERINFO 'n'
//用户信息有效
#define VALID_USERINFO 'y'

//收到的是用户名
#define USERNAME  0
//收到的是密码
#define PASSWORD  1

#define BUFSIZE  1024


//保存用户名密码和结构体的数组
struct userinfo
{
	char username[32];
	char password[32];
};

//以只含有一个空格的字符串作为数组的结束标志
/*struct userinfo users[]=
{
	{"linux","unix"},
	{"4507","4508"},
	{"clh","clh"},
	{"xl","xl"},
	{" "," "}
};*/

void my_err(const char * err_string,int line);
int my_recv(int conn_fd,char * date_buf,int len);
int find_name(const char *name);
void* send_data(void  *client_fd);
void my_sleep();
void *sleepthid(void *b);
#endif
