#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

unsigned int i = 0;

void* fun1(void*);
void* fun2(void*);

pthread_mutex_t lock;

int main()
{
	pthread_t t1,t2;

	pthread_mutex_init(&lock,NULL);
	pthread_create(&t1,NULL,fun1,NULL);
	pthread_create(&t2,NULL,fun2,NULL);
	
	pthread_mutex_destroy(&lock);
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	
	return 0;
}

void *fun1(void *p)
{
	int i;
	char c = 'a';
	pthread_mutex_lock(&lock);
	for(i=0;i<26;i++)
	{
		//usleep(100000);
		printf("%c\n",c+i);
	}
	pthread_mutex_unlock(&lock);
}
void *fun2(void *p)
{
	int i;
	unsigned long m;
	char c = 'A';
	pthread_mutex_lock(&lock);
    for(i=0;i<26;i++)
    {	
		printf("%c\n",c+i);
    }
	pthread_mutex_unlock(&lock);
}
