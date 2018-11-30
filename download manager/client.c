#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

int wait_fun(int);

char path[32] = {0,};

int main(int argc,char**argv)
{	
	char file[32] = {0,};
	
	char k;
	FILE *fp;

	if(argc != 2)
	{
		printf("./a.out src_path\n");
		return (EXIT_SUCCESS);
	}
	
	int sfd,nsfd;
	struct sockaddr_in addr;
	int opt = 1;
	int len = sizeof(addr);
	
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1)
	{
		perror("socket");
		return (EXIT_FAILURE);
	}
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(18082);
	
	if(connect(sfd,(struct sockaddr*)&addr,len) == -1)
	{
		perror("connect");
		return (EXIT_FAILURE);
	}
	
	
	strcpy(path,argv[1]);
	
	int result  = wait_fun(sfd);
	
	return result;
}

int wait_fun(int p)
{	
	char k;
	int id = p;
	printf("id == %d\n",id);	
	FILE *fp = NULL;
	char file[32] = {0,};
	
	printf("in thread path sent = %s\n",path);
	write(id,path,sizeof(path));

	printf("\n%s contains files : \n\n",path);
	while(read(id,file,sizeof(file)) > 0)
	{
		if(strcmp(file,"stop") == 0)
		{
			printf("Directory reading done\n");
			break;
		}
		printf("%s\n",file);
	}
	printf("Enter file name to download : ");
	scanf("%s",file);
	
	write(id,file,sizeof(file));
	
	printf("\n%s is Downloading...\n",file);
	
	fp = fopen(file,"wb");
	
	if(fp == NULL)
	{
		perror("fopen");
		return 1;
	}
	
	system("clear");
	printf("\n\n<<----- Downloading file -- %s -- ---->>-\n\n",file);

	while(read(id,&k,1) > 0)
	{
		if(k == '@')
			break;
		fwrite(&k,sizeof(char),1,fp);
	}
	
	fclose(fp);
	
	printf("Downloading file Done...\n");
	return 0;
}




























