#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void (*p)(int);
	
void sigfpe_handler(int n)
{
	printf("SIGFPE(%d) received\n",n);
}

int main()
{
	int no;
	
	signal(SIGQUIT,SIG_IGN);
	signal(SIGFPE,sigfpe_handler);
	
	printf("Enter signal number to know its default action = ");
	scanf("%d",&no);
	
	p = signal(no,SIG_IGN);
	//signal(no,p);
	if(p == SIG_DFL)
		printf("Default...\n");
	else if(p == SIG_IGN)
		printf("Ignore...\n");
	else
		printf("isr...\n");
	
	return 0;
}
