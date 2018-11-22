#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main()
{
	int pipefd[2];
	char c = 'R';
	unsigned int count = 0;
	
	if(pipe2(pipefd,O_NONBLOCK) == -1)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	
	printf("readend = %d\n",pipefd[0]);
	printf("writeend = %d\n",pipefd[1]);
	
	while(write(pipefd[1],&c,1) != -1)
	{
		count++;
	}
	
	printf("buffer for pipe = %d\n",count);
	
	return (EXIT_SUCCESS);
}
