#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void alarm_handler(int n)
{
	printf("SIGALRM(%d) is received\n",n);
	printf("raise(9) command pid_t = %d\n",getpid());
	raise(9);
}

int main()
{
	printf("Kill procecc after 5 seconds\n");
	signal(SIGALRM,alarm_handler);
	
	alarm(5);
	while(1);
}
