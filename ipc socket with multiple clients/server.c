#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<pthread.h>

void* fun(void*);

int main()
{
		
	int sfd,nsfd;
	struct sockaddr_in addr;
	int opt = 1,i;
	char buf[32];	

	socklen_t len = sizeof(addr);
	
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
	addr.sin_port = htons(18080);
	
	if(bind(sfd,(struct sockaddr*)&addr,len) == -1)
	{
		perror("bind");
		return (EXIT_FAILURE);
	}
	
	if(listen(sfd,5) == -1)
	{
		perror("listen");
		return (EXIT_FAILURE);
	}
	
	printf("Waiting for client...\n");

	
	while(1)
	{
		nsfd = accept(sfd,(struct sockaddr*)&addr,&len);
		pthread_t v;
		
		if(nsfd == -1)
		{
			perror("accept");
			return (EXIT_FAILURE);
		}
		printf("\nConnected\n");
		if( read(nsfd,buf,sizeof(buf))  > 0)
		{
			pthread_create(&v,NULL,fun,buf);
		}
	}
	
	return (EXIT_SUCCESS);
}


void *fun(void *c)
{
	int i;
	char *p = (char*)c;
	for(i=0;p[i];i++)
	{
		printf("%c\n",p[i]);
		sleep(1);
	}
	printf("\n----  done  ---\n");
}

































