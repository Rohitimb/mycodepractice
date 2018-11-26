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

void critical_section_count(int id,struct mybuf *p,int total_count);

int main()
{	
	int id,total_count;	
	key_t key;
	pid_t pid;
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
	total_count = 0;
	while(total_count < 10000)
	{
		printf("Enter count (>= 10000)= ");
		scanf("%d",&total_count);
	}

	p->cnt = 0;
	pid = fork();

	if(pid == 0)
	{//child
		critical_section_count(pid,p, total_count);
		return (EXIT_SUCCESS);
	}
	else
	{//parent
		critical_section_count(pid,p, total_count);
	}
	
	
	while(p->rc != 1)
	{
		printf("Reading not done\n");
		sleep(1);
	}

	if (shmdt(p) == -1) 
	{
		perror("shmdt");
		return (EXIT_FAILURE);
	}

	if (shmctl(id, IPC_RMID, 0) == -1) {
		perror("shmctl");
		return 1;
	}
	printf("Writing Process: Complete\n");	

	return (EXIT_SUCCESS);
}
	
void critical_section_count(int pid,struct mybuf *ptr,int total_count)
{
	int count;
	int i;
	
	ptr->wc = 0;
	count = ptr->cnt;
	
	if(pid == 0)
		printf("Child writing started ... \n");
	else
		printf("parent writing started ... \n");
	
	for(i=0;i<total_count;i++)
	{
		count++;
		ptr->cnt = count;
		if(i%1000 == 0)
		sleep(1);
	}
	
	if(pid == 0)
		printf("Child writing completed ... \n");
	else
		printf("parent writing completed ... \n");
	
	ptr->wc = 1;	
}	
