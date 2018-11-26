#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

int main()
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
	
	if(setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt)) == -1)
	{
		perror("setsockopt");
		return (EXIT_FAILURE);
	}
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(8080);
	
	if(bind(sfd,(struct sockaddr*)&addr,len) == -1)
	{
		perror("bind");
		return (EXIT_FAILURE);
	}
	
	if(listen(sfd,2) == -1)
	{
		perror("listen");
		return (EXIT_FAILURE);
	}
	printf("Waiting for client...\n");
	
	nsfd = accept(sfd,(struct sockaddr*)&addr,&len);
	if(nsfd == -1)
	{
		perror("accept");
		return (EXIT_FAILURE);
	}
	printf("Connection Estblished\n");
	
	read(nsfd,buf,32);
	printf("In server = %s\n",buf);
	
	return (EXIT_SUCCESS);
}





































