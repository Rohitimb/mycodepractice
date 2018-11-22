#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int p[2],q[2];
	char msgbufsnd1[24] = "msg pipe 1";
	char msgbufsnd2[24] = "msg pipe 2";
	char msgbufrcv1[24] = "";
	char msgbufrcv2[24] = "";
	
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

		if(read(p[0],msgbufrcv1,sizeof(msgbufrcv1)) < 0)
		{
			perror("read");
			return (EXIT_FAILURE);
		}
		printf("Received from pipe 1 = %s\n",msgbufrcv1);
		printf("sent from pipe 2 = %s\n",msgbufsnd2);
		if(write(q[1],msgbufsnd2,strlen(msgbufsnd2) + 1) < 0)
		{
			perror("write");
			return (EXIT_FAILURE);
		}
		
	}
	else
	{//parent
		close(p[0]);
		close(q[1]);
		printf("sent from pipe 1 = %s\n",msgbufsnd1);
		if(write(p[1],msgbufsnd1,strlen(msgbufsnd1) + 1) < 0)
		{
			perror("write");
			return (EXIT_FAILURE);
		}

		if(read(q[0],msgbufrcv2,sizeof(msgbufrcv2)) < 0)
		{
			perror("read");
			return (EXIT_FAILURE);
		}
		printf("Received from pipe 2 = %s\n",msgbufrcv2);
	}
	return 0;
}
