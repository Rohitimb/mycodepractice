#include<stdio.h>
#include<pthread.h>

unsigned int i = 0;

//void* fun1(void*);
void* fun2(void*);
void* fun3(void*);
//void* fun4(void*);
void* fun5(void*);
pthread_mutex_t lock;

int main()
{
	pthread_t t1,t2,t3,t4,t5;

	pthread_mutex_init(&lock,NULL);
	//pthread_create(&t1,NULL,fun1,NULL);
	pthread_create(&t2,NULL,fun2,NULL);
	pthread_create(&t3,NULL,fun3,NULL);
	//pthread_create(&t4,NULL,fun4,NULL);
	pthread_create(&t5,NULL,fun5,NULL);
	
	pthread_mutex_destroy(&lock);
	//pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	//pthread_join(t4,NULL);
	pthread_join(t5,NULL);
	
	return 0;
}
#if 0
void *fun1(void *p)
{
	while(1)
	{
		i++;	
		if(i > 100)
			break;
		else
		{
				printf("1 = %d\n",i);
		}
	}
}
#endif
void *fun2(void *p)
{
	pthread_mutex_lock(&lock);
    while(1)
    {
				i++;
        if(i > 100)
            break;
        else
        {
			if(!(i%2))
            {
				printf("2222222222222222 = %d\n",i);
			}	
			else
				pthread_mutex_unlock(&lock);
        }
    }
}

void *fun3(void *p)
{
	pthread_mutex_lock(&lock);
    while(1)
    {
				i++;
        if(i > 100)
            break;
        else
        {
			if(!(i%3))
            {
				printf("333333333333333 = %d\n",i);
			}
			else
				pthread_mutex_unlock(&lock);
        }
    }
}

void *fun5(void *p)
{
	pthread_mutex_lock(&lock);
    while(1)
    {
		i++;
        if(i > 100)
            break;
        else
        {
			if(!(i%5))
	        {
			    printf("5555555555555555 = %d\n",i);
			}
			else
				pthread_mutex_unlock(&lock);
        }
    }
}
#if 0
void *fun1(void *p)
{
    while(1)
    {
        i++;
        if(i > 100)
            break;
        else
        {
            printf("1 = %d\n",i);
        }
    }
}
#endif
