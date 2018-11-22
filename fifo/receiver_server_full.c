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
	
	fd1 = open("fifofile1",O_RDONLY);
	fd2 = open("fifofile2",O_WRONLY);

	if((fd1 == -1) || (fd2 == -1))
	{
		perror("open");
		return (EXIT_FAILURE);
	}

	if(fork() == 0)
	{//child
		while(1)
		{
			if(read(fd1,msgbuf1,sizeof(msgbuf1)) == -1)
			{		
				perror("write");
				return (EXIT_FAILURE);
			}
			printf("String received fom terminal 1 = %s lenght = %lu\n",msgbuf1,strlen(msgbuf1));

			if((strcmp(msgbuf1,"stop") == 0) || (strcmp(msgbuf2,"stop") == 0))
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
			scanf(" %[^\n]",msgbuf2);

			if(write(fd2,msgbuf2,strlen(msgbuf2) + 1) == -1)
			{		
				perror("write");
				return (EXIT_FAILURE);
			}
		}
	}

	return (EXIT_SUCCESS);
}
