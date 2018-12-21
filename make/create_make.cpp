#include<iostream>
#include<sys/types.h>
#include<dirent.h>
#include<cstdio>
#include<cstring>

using namespace std;
bool listFilesFromDirectory(char*);

int main(int argc, char **argv)
{
	bool state = false;
	
	if(argc != 2)
	{
		cout << "./a.out path_to_create_make file" << endl;
		return 1;
	}
	
	cout << "Hello\tWorld"<< endl;
	if(false == listFilesFromDirectory(argv[1]))
	{
		cout << "Not able to create a makefile";
		return 1;
	}

	cout << "job done"<< endl; 
	return 0;	
}

bool listFilesFromDirectory(char *p)
{
	char filename[24] = {0,};
	char make[100] = {0,};
	FILE *fp = NULL;
	char *pt = NULL;
	char str[32] = {0,};
	int c = 0;
	char path[32],temp[32];

	static DIR *ptr = NULL;
	static struct dirent *dp = NULL;

	strcpy(path,p);

	ptr = opendir(path);
	if(ptr == NULL)
	{
		perror("opedir");
		return false;
	}

	fp = fopen("Makefile","w");
	if(fp == NULL)
	{
		perror("fope");
		return false;
	}
	
	while(dp = readdir(ptr))
	{
		memset(make,0x00,sizeof(make));
		
		if(dp->d_name[0] != '.')
		{
			memset(temp,0x00,sizeof(temp));
			strcpy(temp,dp->d_name);
			
			if(0 ==  strcmp(temp+strlen(temp)-4,".cpp"))
			{
				/*creating line for executable*/
				c++;
				strncpy(filename,temp,strlen(temp) - 4);
				filename[strlen(temp)-4] = '\0';
				strcpy(make,filename);
				strcat(make,":");
				strcat(make,filename);
				strcat(make,".o\n");
				cout << make;
				fputs(make,fp);
				
				
				/*creating line for .o and exe*/
				memset(make,0x00,sizeof(make));
				strcpy(make,"\t");
				strcat(make,"$(CXX) ");
				strcat(make,filename);
				strcat(make,".o -o ");
				strcat(make,filename);
				strcat(make,"\n");
				cout << make;
				fputs(make,fp);
					
			
				/*creating line to generate .o files*/
				memset(make,0x00,sizeof(make));
				strcpy(make,filename);
				strcat(make,".o:");
				strcat(make,temp);
				strcat(make,"\n");
				cout <<make;
				fputs(make,fp);
			
				
				/*creating line for .cpp and .o*/
				memset(make,0x00,sizeof(make));
				strcpy(make,"\t");
				strcat(make,"$(CXX) ");
				strcat(make,"-c ");
				strcat(make,temp);
				strcat(make,"\n");
				cout << make << endl;
				fputs(make,fp);
				fputc('\n',fp);
			}	
		}
	}
	fclose(fp);
	cout << "c = " << c << endl;
	
	
	return true;
}

