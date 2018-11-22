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
	char msgbuf[24];

	mkfifo("fifofile",S_IFIFO | 0644);
	perror("mkfifo");
	
	fd = open("fifofile",O_WRONLY);
	if(fd == -1)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	
	while(1)
	{
		printf("Enter string = ");
		//gets(msgbuf);
		scanf(" %[^\n]",msgbuf);
		
		if(write(fd,msgbuf,strlen(msgbuf) + 1) == -1)
		{		
			perror("write");
			return (EXIT_FAILURE);
		}
		if(strcmp(msgbuf,"stop") == 0)
		{
			printf("client stops.. string sent = %s lenght = %lu\n",msgbuf,strlen(msgbuf));
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
