#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	int pipefd[2];
	char msgsnd[24] = "Hello pipe";
	char msgrcv[24] = "Hello pipe";
	
	if(pipe(pipefd) == -1)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	
	printf("readend = %d\n",pipefd[0]);
	printf("writeend = %d\n",pipefd[1]);
	
	printf("message send from pipe = %s\n",msgsnd);
	
	if(write(pipefd[1],msgsnd,strlen(msgsnd)+1) == -1)
	{
		perror("write");
		return (EXIT_FAILURE);
	}
	
	if(read(pipefd[0],msgrcv,sizeof(msgrcv)) == -1)
	{
		perror("read");
		return (EXIT_FAILURE);
	}
	
	printf("message read from pipe = %s\n",msgrcv);
	
	return (EXIT_SUCCESS);
}
