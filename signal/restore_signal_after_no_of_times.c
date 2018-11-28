#include<stdio.h>
#include<signal.h>

int sigIntCount = 0;
int sigQuitCount = 0;

void signal_handler(int n)
{
	if(n == SIGINT)
	{
		sigIntCount++;
		if(5-sigIntCount)
			printf("SIGINT will not work for next %d times\n",5-sigIntCount);
	}
	if(n == SIGQUIT)
	{
		sigQuitCount++;
		if(3-sigQuitCount)
		printf("SIGQUIT will not work for next %d times\n",3-sigQuitCount);
	}
	
	if(sigIntCount == 5)
	{
		signal(SIGINT,SIG_DFL);	
		printf(" SIGINT(%d) is changed to default\n",n);
	}
	if(sigQuitCount == 3)
	{
		signal(SIGQUIT,SIG_DFL);	
		printf(" SIGINT(%d) is changed to default\n",n);
	}
}

int main()
{
	printf("SIGINT(2) is blocked for 5 times\nSIGQUIT(3) is blocked for 3 times\n");
	signal(SIGINT,signal_handler);	
	signal(SIGQUIT,signal_handler);	
	
	while(1);
	return 0;
}
