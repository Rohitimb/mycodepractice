#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void alarm_handler(int n)
{
	signal(SIGINT,SIG_DFL);
	printf("\nSIGINT is changed to default\n");
}

int main()
{
	signal(SIGINT,SIG_IGN);
	signal(SIGALRM,alarm_handler);
	
	printf("SIGINT is blocked for 5 seconds\n");
	alarm(5);
	
	while(1);
	return 0;
}
