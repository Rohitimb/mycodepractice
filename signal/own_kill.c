#include<stdio.h>
#include<sys/types.h>
#include<signal.h>
#include<stdlib.h>

int main(int argc,char**argv)
{
	if(argc != 3)
	{
		printf("Usage:./my_kill signal_number pid_t\n");
		return 1;
	}
	
	if(kill(atoi(argv[2]),atoi(argv[1])) == -1)
	{	
		perror("kill");
		return 1;
	}
	printf("command \"kill -%d %d\" sent\n",atoi(argv[1]),atoi(argv[2]));
	
	return 0;
}
