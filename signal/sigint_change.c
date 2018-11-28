#include<stdio.h>
#include<signal.h>

void sigint_isr(int n)
{
	printf(" SIGINT is blocked use Ctrl + \\ to quit\n");
}
	
int main()
{
	printf("IMB\n");
	signal(SIGINT,sigint_isr);
	while(1);
	
	return 0;
}
