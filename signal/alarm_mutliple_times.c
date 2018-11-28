#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int count = 0;

void alarm_handler(int n)
{
	count--;

	if(count == 0)
	{
		printf("kill process by raise pid_t = %d\n",getpid());
		raise(9);
	}
	else
	{
		printf("\nNew alarm for %d seconds\n",count);
		alarm(count);
	}
}

int main()
{
	count = 5;
	printf("alarm for 5 seconds\n");
	
	signal(SIGALRM,alarm_handler);
	alarm(5);
	
	while(1);
	return 0;
}
