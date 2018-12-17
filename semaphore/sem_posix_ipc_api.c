#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
sem_t m;

void* fun(void *p)
{
	sem_wait(&m);
	printf("Entered ...\n");
	sleep(4);
	printf("Exit ...\n");
	sem_post(&m);
}

int main()
{
	sem_init(&m,0,1);
	
	pthread_t t1,t2;

	if(0 != pthread_create(&t1,NULL,fun,NULL))
	{
		perror("pthread_create");
		return 1;
	}
	sleep(2);
	
	if(0 != pthread_create(&t2,NULL,fun,NULL))
	{
		perror("pthread_create");
		return 1;
	}
	
	if(0 != pthread_join(t1,NULL))
	{
		perror("pthread_join");
		return 1;
	}
	if(0 != pthread_join(t2,NULL))
	{
		perror("pthread_join");
		return 1;
	}

	if(-1 == sem_destroy(&m))
	{
		perror("sem_destroy");
		return 1;
	}
	
	return 0;
}
