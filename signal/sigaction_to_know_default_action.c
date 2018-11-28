#include<stdio.h>
#include<signal.h>

void sigfpe_handler(int n)
{
	printf("SIGFPE(%d) received\n",n);
}
	
int main()
{
	int n;
	struct sigaction v;
	signal(SIGQUIT,SIG_IGN);
	signal(SIGFPE,sigfpe_handler);
	
	printf("Enter the number = ");
	scanf("%d",&n);
	
	sigaction(n,0,&v);
	
	if(v.sa_handler == SIG_DFL)
		printf("Default...\n");
	else if(v.sa_handler == SIG_IGN)
		printf("Ignore...\n");
	else
		printf("isr...\n");
		
	return 0;
}
