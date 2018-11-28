#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int count = 0;

void *even_print(void*);
void *odd_print(void*);
pthread_mutex_t lock;

int main()
{
	pthread_t thread_even,thread_odd;
	
	printf("Even odd printing thread\n");
	
	if(0 != pthread_create(&thread_odd,NULL,odd_print,NULL))
	{
		perror("pthread_create");
		return 1;
	}
		
	if(0 != pthread_create(&thread_even,NULL,even_print,NULL))
	{
		perror("pthread_create");
		return 1;
	}
	
	if(0 != pthread_mutex_init(&lock,NULL))
	{
		perror("pthread_mutex_init");
		return 1;
	}
	if(0 != pthread_join(thread_even,NULL))
	{
		perror("pthread_join");
		return 1;
	}
	if(0 != pthread_join(thread_odd,NULL))
	{
		perror("pthread_join");
		return 1;
	}
	
	pthread_mutex_destroy(&lock);
	printf("\nDone...\n");
	pthread_exit(NULL);
	
	return 0;
}

void *even_print(void* p)
{
	pthread_mutex_lock(&lock);
	while(count < 100)
	{
		sleep(1);
		count++;
		if(count %2 == 0)
		{
			printf("Even = %d\n",count);	
		}
		pthread_mutex_unlock(&lock);
	}
	pthread_exit(NULL);
}

void *odd_print(void* p)
{
	pthread_mutex_lock(&lock);
	while(count < 100)
	{
		sleep(1);
		count++;
		if(count %2)
		{
			printf("Odd  = %d\n",count);
		}
		pthread_mutex_unlock(&lock);
	}
	pthread_exit(NULL);
}
