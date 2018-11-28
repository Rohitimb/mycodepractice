#include<stdio.h>
#include<signal.h>

void sigint_handler(int n)
{
	printf("SIGINT(%d) received\n",n);
}

int main()
{	
	struct sigaction v;
	v.sa_handler = sigint_handler;
	sigemptyset(&v.sa_mask);
	v.sa_flags = 0;

	sigaction(SIGINT,&v,0);
	while(1);
	return 0;
}
