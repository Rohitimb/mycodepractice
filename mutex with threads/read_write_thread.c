#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
	
FILE *fp;
pthread_mutex_t lock;

void fun(int x)
{  
	int i;
	char c;
	
	pthread_mutex_lock(&lock); 
	
	if(x == 2)
		c = 'a';
	if(x == 1)
		c = 'A';
	for(i=0;i<5;i++)
	{
		printf("Will write = %c\n",c+i);
		sleep(1);
		if(fp != NULL)
		{
			fputc(c+i,fp);
		}
	}	

	pthread_mutex_unlock(&lock);
}



void *capital(void *p)
{
	fun(1);
	pthread_exit(NULL);
}

void *small(void *p)
{
	fun(2);
	pthread_exit(NULL);
}

int main()
{
	pthread_t wc,ws;
	
	printf("Thread writing to a file\n");
	
	fp = fopen("myfile.txt","w");
	if(fp == NULL)
	{
		perror("fopen");
		return 1;
	}

	if (pthread_mutex_init(&lock, NULL) != 0) 
	{ 
		printf("mutex init has failed\n"); 
		return 1; 
	} 

	if(0 != pthread_create(&wc,NULL,capital,NULL))
	{
		perror("pthread_create");
		return 1;
	}
	
	if(0 != pthread_create(&ws,NULL,small,NULL))
	{
		perror("pthread_create");
		return 1;
	}
	
	pthread_join(ws,NULL);
	pthread_join(wc,NULL);
	
	printf("close the file\n");
	if(fp)
	{	
		fclose(fp);
	}
	pthread_mutex_destroy(&lock); 
	pthread_exit(NULL);
	return 0;
}
