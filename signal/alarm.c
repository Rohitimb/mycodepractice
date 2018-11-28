#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void alarm_handler(int n)
{
	printf("Alarm signal(%d) Received\n",n);
}

int main()
{	
	signal(SIGALRM,alarm_handler);
	printf("IMB : alarm signal in 5 seconds\n");
	
	alarm(5);
	while(1);
	return 0;
}
