#include<stdio.h>
#include<unistd.h>

int main()
{
	int i =0;
	while(1)
	{
		i++;
		printf("Going to pause after 2 seconds %d\n",i);
		sleep(1);
		if(i == 2)
		{
			printf("paused now pid = %d\n",getpid());
			pause();
		}
	}
	return 0;
}
