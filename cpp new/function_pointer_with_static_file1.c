#include<stdio.h>

extern void (*ptr)();

int main()
{
	ptr();
	
	return 0;
}
