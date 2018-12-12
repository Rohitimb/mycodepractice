#include<iostream>
#include<unistd.h>
#include<thread>
#include<mutex>

void fun1();
void fun2();
void fun3();
void fun4();
void fun5();

int f = 0;

int x = 1;

using namespace std;

int main()
{
	f = 1;
	
	thread t1{fun1};
	thread t2{fun2};
	thread t3{fun3};
	thread t4{fun4};
	thread t5{fun5};

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	
	return 0;
}


void fun1()
{
	while(1)
	{
	
		if(x > 100)
		{
			break;
		}
		else
		{		
			if(f == 1)	
			{
				cout << "thread 1 x = " << x << endl; 
				x++;
				f = 2;
			}
		}
		
	}
}

void fun2()
{
	while(1)
	{
	
		if(x > 100)
		{
			break;
		}
		else
		{		
			if(f == 2)	
			{
				cout << "thread 2 x = " << x << endl; 
				x++;
				f = 3;
			}
		}
	}
}


void fun3()
{
	while(1)
	{
		if(x > 100)
		{
			break;
		}
		else
		{		
			if(f == 3)	
			{
				cout << "thread 3 x = " << x << endl; 
				x++;
				f = 4;
			}
		}
	}
}


void fun4()
{
	while(1)
	{
	
		if(x > 100)
		{
			break;
		}
		else
		{		
			if(f == 4)	
			{
				cout << "thread 4 x = " << x << endl; 
				x++;
				f = 5;
			}
		}
	}
}


void fun5()
{
	while(1)
	{
	
		if(x > 100)
		{
			break;
		}
		else
		{		
			if(f == 5)	
			{
				cout << "thread 5 x = " << x << endl; 
				x++;
				f = 1;
			}
		}
	}
}
