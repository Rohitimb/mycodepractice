 #include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

void *wait_fun(void*);

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
	
	printf("path sent = %s\n",path);
	write(sfd,path,sizeof(path));
	
	pthread_t v;	
	
	if(0 != pthread_create(&v,NULL,wait_fun,&sfd))
	{
		perror("pthread_create");
		return (EXIT_FAILURE);
	}
	
	pthread_join(v,NULL);
	

		
	#if 0
	printf("\n%s contains files : \n\n",path);
	while(read(sfd,file,sizeof(file)) > 0)
	{
		if(strcmp(file,"stop") == 0)
		{
			printf("Directory reading done\n");
			break;
		}
		usleep(100000);
		printf("%s\n",file);
	}
	
	pthread_t v;	
	
	if(0 != pthread_create(&v,NULL,wait_fun,&sfd))
	{
		perror("pthread_create");
		return (EXIT_FAILURE);
	}
	
	pthread_join(v,NULL);
	
	printf("Enter file name to download : ");
	scanf("%s",file);
	
	write(sfd,file,sizeof(file));
	
	printf("\n%s is Downloading...\n",file);
	
	fp = fopen(file,"wb");
	if(fp == NULL)
	{
		perror("fopen");
		return (EXIT_FAILURE);
	}
	
	while(read(sfd,&k,1) > 0)
	{
		system("clear");
		usleep(8000);
		printf("\n\n<<----- Downloading file -- %s -- ---->>-\n\n",file);
		usleep(8000);
		
		if(k == 'x')
		{
			printf("Dwonloading done\n");
			break;
		}
		//printf("%c",k);
		fwrite(&k,sizeof(char),1,fp);
	}
	fclose(fp);
	
	printf("Downloding file Done...\n");
	#endif
	return (EXIT_SUCCESS);
}

void *wait_fun(void* p)
{	
	char k;
	int *ptr_id = (int*)p;
	int id = *ptr_id;
		
	FILE *fp = NULL;
	char file[32] = {0,};
	
	#if 0	
	printf("in thread path sent = %s\n",path);
	write(id,path,sizeof(path));
	#endif

	printf("\n%s contains files : \n\n",path);
	while(read(id,file,sizeof(file)) > 0)
	{
		if(strcmp(file,"stop") == 0)
		{
			printf("Directory reading done\n");
			break;
		}
		usleep(100000);
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
		return (void*)(EXIT_FAILURE);
	}
	
	while(read(id,&k,1) > 0)
	{
		system("clear");
		usleep(8000);
		printf("\n\n<<----- Downloading file -- %s -- ---->>-\n\n",file);
		usleep(8000);
		
		if(k == 'x')
		{
			printf("Dwonloading done\n");
			break;
		}
		//printf("%c",k);
		fwrite(&k,sizeof(char),1,fp);
	}
	fclose(fp);
	
	printf("Downloding file Done...\n");
	pthread_exit(NULL);
}


































