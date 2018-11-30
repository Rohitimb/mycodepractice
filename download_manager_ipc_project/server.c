#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<pthread.h>

void *thread_fun(void*);
int sent_file_to_client(int,char*,char*);

int main(int argc,char**argv)
{
	DIR *p;
	struct dirent *dp;
		
	FILE *fp;
	char s[32] = {0,};
	int sfd;
	struct sockaddr_in addr;
	int opt = 1;
	char buf[32] = {0,};
	
	pthread_t v;
	int len = sizeof(addr);
	
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1)
	{
		perror("socket");
		return (EXIT_FAILURE);
	}
	printf("Server sfd = %d\n",sfd);
	
	if(setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt)) == -1)
	{
		perror("setsockopt");
		return (EXIT_FAILURE);
	}
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(18082);
	
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
		int nsfd = accept(sfd,(struct sockaddr*)&addr,&len);
		if(nsfd == -1)
		{
			perror("accept");
			return (EXIT_FAILURE);
		}
	
		
		printf("Connection Estblished id = %d\n",nsfd);
		
		if(0 != pthread_create(&v,NULL,thread_fun,&nsfd))
		{
			perror("pthread_create");
			return (EXIT_FAILURE);
		}
	}
	pthread_exit(NULL);//code will not reach here
}

void* thread_fun(void *ptr)
{
	DIR *p;
	char file[32] = {0,};
	char path[32] = {0,};
	struct dirent *dp;
	int id = *((int*)ptr);
	FILE *fp;
	char a,m;
	char path_file[64] = {0,};
	long int size;
	
	if(read(id,path,sizeof(path)) <= 0)
	{
		return (void*)-1;
	}
	
	printf("In thread path = %s server nsfd = %d\n",path,id);
	
	p = opendir(path);
	
	if(p == NULL)
	{
		perror("opendir");
		return (void*)-1;
	}
	

	while((dp = readdir(p)) != NULL)
	{
		if(dp->d_name[0] != '.' && dp->d_type == DT_REG)
		{
			strcpy(file,dp->d_name);
			write(id,file,sizeof(file));
			printf("%s\n",dp->d_name);
		}
	}
	
	closedir(p);
 
	strcpy(file,"stop");
	write(id,file,sizeof(file));
	
	printf("\nWaiting for clinet to select file to download...\n\n");
	
	if(read(id,file,sizeof(file)) <= 0)
	{
		perror("read");
		return (void*)-1;
	}
	printf("%s sending started\n",file);

	
	strcpy(path_file,path);
	strcat(path_file,file);
	
	fp=fopen(path_file,"rb");
	if(fp == NULL)
	{
		perror("fopen");
		return(void*) -1;
	}
	
	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	fseek(fp,0,SEEK_SET);    // same as rewind(fp)
	
	printf("File to be sent is = %s file size = %ld\n",path_file,size);
	for(int i=0;i<size;i++)
	{
		m = a;
		fread(&m,sizeof(char),1,fp); 
		write(id,&m,sizeof(char));
	}
	
	m = '@';
	write(id,&m,sizeof(char));
	fclose(fp);
	
	printf("%s file sent\n",path_file);
	printf("\n -----------%d  Done serving ----------- \n",getpid());
	pthread_exit(NULL);
}

