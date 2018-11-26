#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>

struct mybuf
{
	int cnt;
	int wc;
	int rc;
};

int main()
{	
	int id,total_count;	
	key_t key;
	struct mybuf *p;
	
	key = ftok("data.txt",65);
	if(key == -1)
	{
		perror("ftok");
		return (EXIT_FAILURE);
	}
	
	id =  shmget(key,sizeof(struct mybuf),IPC_CREAT|0666);
	if(id == -1)
	{
		perror("shmget");
		return (EXIT_FAILURE);
	}
	
	p = shmat(id,NULL,0);
	if(p == (void*)-1)
	{
		perror("shmat");
		return (EXIT_FAILURE);
	}
		
	while(p->wc != 1)
	{
		printf("writing not done\n");
		sleep(1);
	}
	printf("count = %d\n",p->cnt);
	p->rc = 1;
	
	printf("Reading Done..\n");
	return (EXIT_SUCCESS);
}	
