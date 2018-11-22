#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>

int main()
{
	int p[2],q[2],i;
	char msgbufsnd[24] = "msg to be send";
	char msgbufrcv[24] = "";
	
	if(pipe(p) < 0)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	
	if(pipe(q) < 0)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	
	if(fork() == 0)
	{//child
		close(p[1]);
		close(q[0]);

		if(read(p[0],msgbufrcv,sizeof(msgbufrcv)) < 0)
		{
			perror("read");
			return (EXIT_FAILURE);
		}
		printf("Received from pipe 1 = %s\n",msgbufrcv);
		for(i=0;msgbufrcv[i];i++)
		{
			if(islower(msgbufrcv[i]))
				msgbufrcv[i] = toupper(msgbufrcv[i]);
		}
		printf("sent from pipe 2 = %s\n",msgbufrcv);
		if(write(q[1],msgbufrcv,strlen(msgbufrcv) + 1) < 0)
		{
			perror("write");
			return (EXIT_FAILURE);
		}
		
	}
	else
	{//parent
		close(p[0]);
		close(q[1]);
		printf("sent from pipe 1 = %s\n",msgbufsnd);
		if(write(p[1],msgbufsnd,strlen(msgbufsnd) + 1) < 0)
		{
			perror("write");
			return (EXIT_FAILURE);
		}

		if(read(q[0],msgbufrcv,sizeof(msgbufrcv)) < 0)
		{
			perror("read");
			return (EXIT_FAILURE);
		}
		printf("Received from pipe 2 = %s\n",msgbufrcv);
	}
	return 0;
}
