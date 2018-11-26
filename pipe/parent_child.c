#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	int pipefd[2];
	char msgsnd[24] = "Hello pipe";
	char msgrcv[24];
	
	if(pipe(pipefd) == -1)
	{
		perror("pipe");
		return (EXIT_SUCCESS);
	}	
	
	printf("readend of pipe = %d\n",pipefd[0]);
	printf("writeend of pipe = %d\n",pipefd[1]);
	
	if(fork() == 0)
	{//child
		if (read(pipefd[0],msgrcv,sizeof(msgrcv)) == -1)
		{
			perror("read");
			return (EXIT_SUCCESS);
		}
		printf("reading from pipe in child process = %s\n",msgsnd);
	}
	else
	{//parent
		printf("writing to pipe in parent process = %s\n",msgsnd);
		if (write(pipefd[1],msgsnd,strlen(msgsnd)+1) == -1)
		{
			perror("write");
			return (EXIT_SUCCESS);
		}
	}
	
	return (EXIT_SUCCESS);
}
