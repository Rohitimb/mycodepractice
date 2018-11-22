#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	int fd;
	char msgbuf[24] = "";
	
	mkfifo("fifofile",S_IFIFO | 0644);
	perror("mkfifo");
	
	fd = open("fifofile",O_RDONLY);
	
	if(fd == -1)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	
	while(1)
	{
		read(fd,msgbuf,sizeof(msgbuf));
		printf("string received = %s lenght = %lu\n",msgbuf,strlen(msgbuf));
		if(read(fd,msgbuf,sizeof(msgbuf)) != 0)
		{
			printf("string received = %s lenght = %lu\n",msgbuf,strlen(msgbuf));
		}
		if(strcmp(msgbuf,"stop") == 0)
		{
			printf("Server stops.. string received = %s lenght = %lu\n",msgbuf,strlen(msgbuf));
			if(close(fd) == -1)
			{
				perror("close");
				return (EXIT_FAILURE);
			}
			break;
		}
	}
	return (EXIT_SUCCESS);
}
