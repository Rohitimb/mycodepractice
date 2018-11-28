#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void* fun(void *p)
{
	sleep(1);
	printf("thread\n");
	pthread_exit(NULL);
}

int main()
{
	pthread_t v;	
	
	int i;
	for(i=0;i<10;i++)
	{
		if(0 != pthread_create(&v,NULL,fun,NULL))
		{
			printf("Error\n");	
			return 1;
		}
		printf("created\n");

	}
	pthread_exit(NULL);
	
	return 0;
}
