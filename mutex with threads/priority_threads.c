#include<stdio.h>      
#include<stdlib.h>
#include<pthread.h>  
#include<sched.h>     

void *thread_fun(void *);

#define MAX 5
#define CHANGE 2

int main()
{
	pthread_t var[MAX],main_id;
	pthread_attr_t attr[MAX];
	
	struct sched_param param;
	
	int policy=SCHED_FIFO;
	int min,max;

	unsigned long mask = 1; /* use only 1 CPU core */
	unsigned int len = sizeof(mask);
	
	if(0 != sched_setaffinity(0, len, &mask))
	{
		perror("sched_setaffinity");
		return 1;
	}
	if(0 != sched_getaffinity(0, len, &mask))
	{
		perror("sched_getaffinity");
		return 1;
	}
	
	max = sched_get_priority_max(SCHED_FIFO);
	min = sched_get_priority_min(SCHED_FIFO);

	main_id = pthread_self();
	param.sched_priority = max;
	
	if(0 != pthread_setschedparam(main_id, policy, &param))
	{
		perror("pthread_setschedparam");
		return 1;
	}
	
	for(int  i=0;i<MAX;i++)
	{
		if(i == CHANGE)
		{
			/*changing the priority*/
			param.sched_priority = 30;
		}
	
		if(0 != pthread_attr_init(&attr[i]))
		{
			perror("pthread_attr_init");
			return 1;
		}

		if(0 != pthread_attr_setschedpolicy(&attr[i],policy))
		{
			perror("pthread_attr_setschedpolicy");
			return 1;
		}

		if(0 != pthread_attr_setschedparam(&attr[i],&param))
		{
			perror("pthread_attr_setschedparam");
			return 1;
		}
	
		int *p1 = (int*)malloc(sizeof(int));
		*p1 = i;

		if(0 != pthread_create(&var[i], &attr[i], thread_fun,p1))
		{
			perror("pthread_create");
			return 1;
		}
		if(0 != pthread_setschedparam(var[i],policy,&param))
		{
			perror("pthread_setschedparam");
			return 1;
		}
	}
	for(int i=0;i<MAX;i++)
	{
		if(0 != pthread_join(var[i], NULL))
		{
			perror("pthread_join(var, NULL)");
			return 1;
		}
	}
		
	for(int i=0;i<MAX;i++)
	{
		if(0 != pthread_attr_destroy(&attr[i]))
		{
			perror("pthread_attr_destroy");
			return 1;
		}
	}
	
	pthread_exit(NULL);
	return 0;		
}

void *thread_fun(void *ptr)
{
	int j,i;
	int *p = (int*)ptr;
	printf("Thread start = %d\n",*p);

	for(i=0;i<2;i++)
	{
		for(j=1;j<=100000000;j++)
		{
			//do operation just going through the loop
		}
	}
	printf("Thread end = %d\n",*p);

	pthread_exit(NULL);
	
	return NULL;
}

