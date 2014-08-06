#include "ls.h"
//检查用户名下标sdaasd
/*int find_name(const char *name)
{
	int i;

	if (name == NULL)
	{
		printf("NULL NAME");
		return -2;
	}
	for(i=0;users[i].username[0] != ' ';i++)
	{
		if(strcmp(users[i].username,name)==0)
			return i;
	}
	return i;
}*/

void* send_data(void *client_fd)
{
	char send_msg[200];

	while (1) 
	{
		printf("请输入要发送的信息：");
		fgets(send_msg,sizeof(send_msg),stdin);

		if (send_msg[strlen(send_msg) - 1] == '\n') 
		{
			send_msg[strlen(send_msg) - 1] = '\0';
		}

		if (send(*(int *)client_fd,send_msg,sizeof(send_msg),0) == -1) 
		{
			perror("发送消息出错");
			exit(1);
		}
	}
}

void my_err(const char *err_string,int line)
{
printf("line is %d",line);
perror(err_string);
exit(1);
}

void my_sleep()
{
	 int i = 1;
        while(i++<7)
        {
                printf(".");
                fflush(stdout);
              usleep(300000);
        }
        sleep(1);
	printf("\n");		

}
void *sleepthid(void *b)
{
//printf("%d",(*(int*)(b)));
while((*(int*)(b))==0)
{
	   int i = 1;
        while(i++<7)
        {
                printf(".");
                fflush(stdout);
              usleep(300000);
        }
        usleep(100000);
	printf("\b\b\b\b\b\b      \b\b\b\b\b\b");
}
}
