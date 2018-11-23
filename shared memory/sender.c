#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<unistd.h>
	
struct msgbuf
{
	char str[32];
	int flag;
};


int main()
{
	int id,i;
	int SHM_KEY = 5;
	
	struct msgbuf *s;	

	id = shmget(SHM_KEY,sizeof(struct msgbuf),IPC_CREAT | 0644);
	if(id == -1)
	{
		perror("shmget");
		return (EXIT_FAILURE);
	}
	printf("Shared memory segment id = %d\n",id);
	
	s = shmat(id,NULL,0);
	if(s == (void*)-1)
	{
		perror("shmat");
		return (EXIT_FAILURE);
	}	

	strcpy(s->str,"This is just a test message");
	
	for(i=0;i<5;i++)
	{
		s->flag = i+1;
		printf("[%d] Message\n%s\n",s->flag,s->str);
		sleep(2);
	}	
	printf("Writing to shared memory done...\n");
	s->flag = 0;
	
	if(shmdt(s) == -1)
	{
		perror("shmdt");
		return (EXIT_FAILURE);
	}
	
	printf("Shared memory segment detached\n");
	if(shmctl(id,IPC_RMID,0) == -1)
	{
		perror("shmctl");
		return (EXIT_FAILURE);
	}
	
	printf("Shared memory segment deleted\n");
	return (EXIT_SUCCESS);
}
