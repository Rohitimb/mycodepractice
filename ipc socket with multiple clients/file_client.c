#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

struct info
{
	char spath[32];
	char dfile[32];
};

int main(int argc,char**argv)
{	
	struct info v;
	if(argc != 3)
	{
		printf("./a.out src_path destination file name.txt\n");
		return (EXIT_SUCCESS);
	}
	
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
	addr.sin_port = htons(18085);
	
	if(connect(sfd,(struct sockaddr*)&addr,len) == -1)
	{
		perror("connect");
		return (EXIT_FAILURE);
	}
	
	strcpy(v.spath,argv[1]);
	strcpy(v.dfile,argv[2]);
	
	send(sfd,&v,sizeof(v),0); 
	printf("message sent\n"); 
	
	return (EXIT_SUCCESS);
}





































