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
	int id;	
	int i;	
	char s[32];

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

	printf("Enter type and Message(24) : ");
	scanf("%d %s",&i,s);
	
	m.mtype = i;
	strcpy(m.msg,s);

	if(msgsnd(id,&m,sizeof(m),0) == -1)
	{
		perror("msgsnd");
		return (EXIT_FAILURE);
	}
	printf("Message sent\n");
	
	return (EXIT_SUCCESS);
}
