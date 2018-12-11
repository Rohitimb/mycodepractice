#include<stdio.h>
#include<stdlib.h>

int main()
{
	int *p;
	
	p = (int*)malloc(sizeof(int));
	
	printf("done\n");
	free(p);
	p = NULL;
		
	free(p);
	free(p);
	free(p);
	free(p);
	
	printf("done\n");

	return 0;
}
