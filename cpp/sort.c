#include <stdio.h>
#include<stdlib.h>

#include <string.h>
int main()
{
    char s[][10] ={"asd","asf","asg","abs"};
    int i,j,n,m;
    n = sizeof(s)/sizeof(s[0]);
    char *t = (char*)malloc(10);
    int min;

    for(i = 0;i < n-1;i++)
    {
        min = i;
        for(j = i+1; j < n;j++)
        {
            if(strcmp(s[j],s[min]))
            {
                min = j;
            }
        }
        if(i != min)
        {
            strcpy(t,s[i]);
            strcpy(s[i],s[min]);
            strcpy(s[min],t);
        }
    }

    for(i=0;i<n;i++)
    	printf("%s\n",s[i]);
    return 0;
}
