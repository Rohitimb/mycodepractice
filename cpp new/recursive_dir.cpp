#include<iostream>
#include<sys/types.h>
#include<dirent.h>
#include<cstdio>
#include<cstring>

using namespace std;
void listFilesFromDirectory(char*);

int main(int argc, char **argv)
{

	if(argc != 2)
	{
		cout << "./a.out path" << endl;
		return 1;
	}
	
	listFilesFromDirectory(argv[1]);

	cout << "job done"<< endl; 
	return 0;	
}

void listFilesFromDirectory(char *p)
{
	int c = 0;
	char path[32],temp[32];

	static DIR *ptr = NULL;
	static struct dirent *dp = NULL;

	strcpy(path,p);

	ptr = opendir(path);
	if(ptr == NULL)
	{
		//perror("opedir");
		return;
	}
	
	if(dp = readdir(ptr))
	{
		if(dp->d_name[0] != '.')
		{
			if(dp->d_type == DT_DIR)
			{
				c++;
				//cout << "found " << endl;
				strcpy(temp,path);
				strcat(temp,dp->d_name);
				//printf("path = %s\n",temp);
				strcpy(path,temp);
				listFilesFromDirectory(path);
			}
			else
				listFilesFromDirectory(path);
			
			cout << dp->d_name << " = " << (int)dp->d_type << endl;
		}
	}
	else
		return;
	cout << "c = " << c << endl;
}


