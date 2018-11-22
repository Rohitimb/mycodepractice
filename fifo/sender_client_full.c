#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	int fd1,fd2,i;
	char msgbuf1[24],msgbuf2[24];

	mkfifo("fifofile1",S_IFIFO | 0644);
	perror("mkfifo");
	
	mkfifo("fifofile2",S_IFIFO | 0644);
	perror("mkfifo");
	
	fd1 = open("fifofile1",O_WRONLY);
	fd2 = open("fifofile2",O_RDONLY);

	if((fd1 == -1) || (fd2 == -1))
	{
		perror("open");
		return (EXIT_FAILURE);
	}

	if(fork() == 0)
	{//child
		while(1)
		{
			if(read(fd2,msgbuf2,sizeof(msgbuf2)) == -1)
			{		
				perror("write");
				return (EXIT_FAILURE);
			}
			printf("String received fom terminal 2 = %s lenght = %lu\n",msgbuf2,strlen(msgbuf2));
			if(strcmp(msgbuf2,"stop") == 0)
			{
				printf("communication stops\n");
				if((close(fd1) == -1) || (close(fd2) == -1))
				{
					perror("close");
					return (EXIT_FAILURE);
				}
				break;
			}
		}
	}
	else
	{//parent
		while(1)
		{
			printf("\nEnter string = ");
			scanf(" %[^\n]",msgbuf1);

			if(write(fd1,msgbuf1,strlen(msgbuf1) + 1) == -1)
			{		
				perror("write");
				return (EXIT_FAILURE);
			}
		}
	}

	return (EXIT_SUCCESS);
}
