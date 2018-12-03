#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int count = 0;
int evenOddflag = 1;

void *even_print(void*);
void *odd_print(void*);

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
	
	printf("\nDone...\n");
	
	return 0;
}

void *even_print(void* p)
{
	while(1)
	{
		if (evenOddflag == 0)
		{
			count++;
			if(count > 100)
			{
		        	evenOddflag = 1;
				break;
			}
			if(count %2 == 0)
			{
				printf("Even = %d\n",count);	
			}
		   	evenOddflag = 1;
		}
	}
	pthread_exit(NULL);
}

void *odd_print(void* p)
{
	while(1)
	{
		if (evenOddflag) 
		{
			count++;
			if(count > 100)
			{
				evenOddflag = 0;
				break;
			}
			if(count %2)
			{
				printf("Odd  = %d\n",count);
			}
			evenOddflag = 0;
		}
	}
	pthread_exit(NULL);
}
