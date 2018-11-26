#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/sem.h>
#include<errno.h>

struct mybuf
{
	int cnt;
	int wc;
	int rc;
};

key_t org;
void remove_semaphore();
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
	total_count = 10000;
	while(total_count < 10000)
	{
		printf("Enter count (>= 10000)= ");
		scanf("%d",&total_count);
	}

	p->cnt = 0;
	pid = fork();
	
	if(pid > 0)
	{//parent
		critical_section_count(pid,p, total_count);
		return (EXIT_SUCCESS);
	}
	else if(pid == 0)
	{//child
		critical_section_count(pid,p, total_count);
	}
	else
	{
		perror("fork");
		return (EXIT_FAILURE);
	}	
	
	while(p->rc != 1)
	{
		//printf("Reading not done\n");
		sleep(1);
	}

	if (shmdt(p) == -1) 
	{
		perror("shmdt");
		return (EXIT_FAILURE);
	}

	if (shmctl(id, IPC_RMID, 0) == -1) 
	{
		perror("shmctl");
		return (EXIT_FAILURE);
	}
	
	printf("Writing Process: Complete\n");	
	remove_semaphore();
	
	return (EXIT_SUCCESS);
}

void critical_section_count(int pid,struct mybuf *ptr,int total_count)
{
	int count;
	int i;
	struct sembuf sem_buf;
	key_t key;
	int semid;	
	int retval;
	
	key = ftok("data.txt",77);
	
	if(key == -1)
	{
		perror("ftok");
		return;
	}
	
	semid = semget(key,1,IPC_CREAT|IPC_EXCL|0666);
	org = key;
	if(semid > 0)
	{//release resource
		printf("Entered first time\n");
		sem_buf.sem_num = 0;
		sem_buf.sem_op = 1;
		sem_buf.sem_flg = 0;

		retval = semop(semid, &sem_buf, 1);	
		if (retval == -1) 
		{
			perror("semop");
			return;
		}
	}
	else if(errno == EEXIST)
	{
		printf("Entered Second time\n");
		semid = semget(key, 1, 0);
		
		if(semid == -1) 
		{
			perror("seget");
			return;
		}

		//Waiting for the resource
		sem_buf.sem_num = 0;
		sem_buf.sem_op = 0;
		sem_buf.sem_flg = SEM_UNDO;
		retval = semop(semid, &sem_buf, 1);
		
		if (retval == -1) 
		{
			perror("Semaphore Locked: ");
        		return;
      		}
	}
	
	sem_buf.sem_num = 0;
	sem_buf.sem_op = -1; /* Allocating the resources */
	sem_buf.sem_flg = SEM_UNDO;
	retval = semop(semid, &sem_buf, 1);
	
	if (retval == -1) 
	{
	      perror("semop");
		      return;
   	}
	
	count = ptr->cnt;
	ptr->wc = 0;

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
 
	ptr->wc = 1;	
	sem_buf.sem_op = 1; /* Releasing the resource */
	retval = semop(semid, &sem_buf, 1);
	
	if (retval == -1) 
	{
		perror("semop\n");
		return;
	}

	if(pid == 0)
		printf("Child writing completed ... \n");
	else
		printf("parent writing completed ... \n");
	return;
}	

void remove_semaphore() 
{
	int semid;
	int retval;
	
	semid = semget(org,1, 0);
	
	if(semid < 0) 
	{
		perror("semget");
		return;
	}
	
	retval = semctl(semid, 0, IPC_RMID);
	printf("id to be removed = %d\n",semid);	
	if(retval == -1) 
	{
		perror("semctl");
		return;
	}
	return;
}
