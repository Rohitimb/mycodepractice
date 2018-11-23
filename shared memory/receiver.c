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

	while(s->flag != 0)
	{	
		printf("[%d] string received\n%s\n",s->flag,s->str);
		sleep(2);
	}

	printf("Reading from shared memory done...\n");
	
	if(shmdt(s) == -1)
	{
		perror("shmdt");
		return (EXIT_FAILURE);
	}
	
	printf("Shared memory segment detached\n");
	
	return (EXIT_SUCCESS);
}
