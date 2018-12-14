#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sched.h>
#include <errno.h>
#include<stdlib.h>

void *thread_fun(void*);

struct sched_param sch;
pthread_attr_t att;

int main()
{
	int i;
	int policy;
	
	pthread_t v[5];

	printf("Thread 3 is having highest priority\n");
	
	if(0 != pthread_attr_init(&att))
	{
		perror("pthread_attr_init");
		return 1;
	}

    pthread_getschedparam(v[2],&policy, &sch);
	perror("thread_getschedparam");
	printf("policy = %d priority = %d\n",policy,sch.sched_priority);

	policy = SCHED_RR;
	sch.sched_priority = 25;
	pthread_setschedparam(v[2],policy,&sch);
	perror("thread_getschedparam");
	printf("policy = %d priority = %d\n",policy,sch.sched_priority);

    pthread_getschedparam(v[2],&policy, &sch);
	perror("thread_getschedparam");
	printf("policy = %d priority = %d\n",policy,sch.sched_priority);
	
	#if 0
   	if(0 != pthread_attr_getschedparam((const pthread_attr_t *)&att,&policy))
	{	
		perror("pthread_attr_getschedparam");
		return 1;
	}
	printf("policy = %d\n",policy);
	
	policy = SCHED_RR;
	
   	if(0 != pthread_attr_setschedpolicy(&att,policy))
	{	
		perror("pthread_attr_setschedparam");
		return 1;
	}
	printf("policy = %d\n",policy);
   	
   	if(0 != pthread_attr_getschedparam((const pthread_attr_t *)&att,&policy))
	{	
		perror("pthread_attr_getschedparam");
		return 1;
	}
	printf("policy = %d\n",policy);

	
	#if 1
	if(0 != pthread_attr_getschedparam(&att,&sch))
	{
		perror("pthread_attr_getschedparam");
		return 1;
	}
	printf("\nScheduling Priority = %d\n",sch.sched_priority);
	(sch.sched_priority) = 25;

	int retval = 0;	
	if( (retval = pthread_attr_setschedparam(&att,(const struct sched_param*)&sch)) )
	{
		perror("pthread_attr_setschedparam");
		printf("Error no: %d retval (%d) \n",errno, retval);
		//return 1;
	}
	

	if(0 != pthread_attr_getschedparam(&att,&sch))
	{
		perror("pthread_attr_getschedparam");
		return 1;
	}
	printf("\nScheduling Priority = %d\n",sch.sched_priority);
	#endif
	#endif
	for(i=0;i<5;i++)
	{
		if(i == 2)
		{
			int *param = (int*)malloc(sizeof(int));
			*param = i;
	
			policy = SCHED_RR;
			sch.sched_priority = 25;
			pthread_setschedparam(v[i],policy,&sch);
	
			if(0 != pthread_create(&v[i],&att,thread_fun,(void*)param))
			{
				perror("pthread_create");
				return 1;
			}
		}
		else
		{
			int *param2 = (int*)malloc(sizeof(int));
			*param2 = i;
			if(0 != pthread_create(&v[i],NULL,thread_fun,(void*)param2))
			{
				perror("pthread_create");
				return 1;
			}
		}
    	pthread_getschedparam(v[i],&policy, &sch);
		printf("thread = %d policy = %d priority = %d\n",i,policy,sch.sched_priority);
	}
	
	
	for(i=0;i<5;i++)
	{
		if(0 != pthread_join(v[i],NULL))
		{
			perror("pthread_join");
			return 1;
		}
	}
	
	if(0 != pthread_attr_destroy(&att))
	{
		perror("pthread_attr_destroy");
		return 1;
	}
	pthread_exit(NULL);
	
	printf("Done, in main function now\n");
	
	return 0;
}

void* thread_fun(void* p)
{
	int *var = (int*)p;
	int i;
//	printf("Start work thread %d \n",*var);
	
	for(i=0;i<200000000;i++)
	{
		//sleep(1);
	}
	
	printf("End work thread %d \n",*var);
	free(var);
	
	pthread_exit(NULL);
}

