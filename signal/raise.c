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
			printf("signal \"Floating point exception\" to current process\n");
			if(0 != raise(8))//floating point exception
			{
				perror("raise");
				return 1;
			}
		}
	}
	return 0;
}
