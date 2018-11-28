#include<stdio.h>
#include<signal.h>

int main()
{
	printf("SIGINT is ignored\n");
	signal(SIGINT,SIG_IGN);
	while(1);
	return 0;
}
