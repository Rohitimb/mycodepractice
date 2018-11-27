#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<pthread.h>

void *fun(void*);

struct info 
{
	char spath[32];
	char dfile[32];
};

int main(int argc,char**argv)
{
	struct info v;
	DIR *p;
	struct dirent *dp;
		
	FILE *fp;
	char s[32] = {0,};
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
	addr.sin_port = htons(18085);
	
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
	
	while(nsfd != -1)
	{
		nsfd = accept(sfd,(struct sockaddr*)&addr,&len);
		if(nsfd == -1)
		{
			perror("accept");
			return (EXIT_FAILURE);
		}
		printf("Connection Estblished %d\n",nsfd);
		
		//printf("In server = path = %s dfile = %s\n",v.spath,v.dfile);
		
		pthread_t v;
		
		pthread_create(&v,NULL,fun,&nsfd);
	}
	
	return (EXIT_SUCCESS);
}


static int m = 0;



void* fun(void *ptr)
{
	FILE *fp;
	DIR *p;
	struct dirent *dp;
	int *id = (int*)ptr;
	printf("in thread = %d\n",*id);
	
	struct info v;
	memset(&v,0x00,sizeof(struct info ));
		
	if(read(*id,&v,sizeof(v)) <= 0)
	{
		return (void*)-1;
	}
	
	printf("In thread = path = %s dfile = %s\n",v.spath,v.dfile);
	
	p = opendir(v.spath);
	if(p == NULL)
	{
		perror("opendir");
		return (void*)-1;
	}
	
	fp = fopen(v.dfile,"w");
	if(fp == NULL)
	{
		perror("fopen");
		return (void*)-1;
	}	
	while((dp = readdir(p)) != NULL)
	{
		sleep(3);
		if(dp->d_name[0] != '.')
		{
			printf("%s\n",dp->d_name);
			fputs(dp->d_name,fp);
			fputc('\n',fp);
		}

	}
	printf("\n -----------%d  Done serving ----------- \n",getpid());
	fclose(fp);
}





























