#include<stdio.h>
#include<signal.h>

void sigint_handler(int n)
{
	signal(SIGINT,SIG_DFL);
	printf(" SIGINT is Changed to default now\n");
}

int main()
{
	printf("SIGINT is handled\n");
	signal(SIGINT,sigint_handler);
	while(1);
	return 0;
}
