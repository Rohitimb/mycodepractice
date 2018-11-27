#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

int main(int argc,char**argv)
{
		
	int sfd,nsfd;
	struct sockaddr_in addr;
	int opt = 1;
	char buf[32] = {0,};
	
	int len = sizeof(addr);
	
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1)
	{
		perror("socket");
		return (EXIT_FAILURE);
	}
	
	
	addr.sin_family = AF_INET;
	//addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(18080);
	
	if(connect(sfd,(struct sockaddr*)&addr,len) == -1)
	{
		perror("connect");
		return (EXIT_FAILURE);
	}
	
	if(argc!= 2){
	printf("Enter Message to sent = ");
	scanf("%[^\n]",buf);
	}
	else
	{
		strcpy(buf,argv[1]);
	}
	send(sfd,buf,strlen(buf)+1, 0); 
	printf("message sent\n"); 
	
	return (EXIT_SUCCESS);
}





































