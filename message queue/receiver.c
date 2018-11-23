#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

struct my_msgbuf
{
	long mtype;
	char msg[32];
};

int main()
{
	static struct my_msgbuf m;
	key_t key;
	int id,m_id;	
		
        key = ftok("data.txt", 65);
	if(key == -1)
	{
		perror("ftok");
		return (EXIT_FAILURE);
	}

	id = msgget(key,IPC_CREAT | 0666);
	if(id == -1)
	{
		perror("msgget");
		return (EXIT_FAILURE);
	}
	printf("Enter key = ");
	scanf("%d",&m_id);

	if(m_id == 0)
	{
		if(msgctl(id,IPC_RMID,0) == -1)
		{
			perror("msgctl");
			return (EXIT_FAILURE);
		}
		printf("Message queue deleted...\n");
		return (EXIT_SUCCESS);
	}
	if(msgrcv(id,&m,sizeof(m),m_id,0) == -1)
	{
		perror("msgrcv");
		return (EXIT_FAILURE);
	}
	
	printf("Data = %s\n",m.msg);
	
	return (EXIT_SUCCESS);
}
