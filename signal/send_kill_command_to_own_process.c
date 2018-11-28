#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>

int main()
{
	int i;
	for(i=0;1;i++)
	{
		printf("IMB %d\n",i);
		sleep(1);
		
		if(i == 4)
		{
			printf("Killing current process\n");
			kill(getpid(),9);
		}
	}
	return 0;
}
