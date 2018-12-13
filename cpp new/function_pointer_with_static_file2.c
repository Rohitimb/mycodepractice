#include<stdio.h>

static void fun()
{
	printf("in file 1\n");
}

void (*ptr)() = fun;
