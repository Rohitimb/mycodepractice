#include<iostream>
#include<unistd.h>
#include<thread>
#include<mutex>

void fun1();
void fun2();
void fun3();
void fun4();
void fun5();

int x = 1;

using namespace std;

mutex m;

int main()
{
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
	m.lock();

	while(1)
	{
	
		if(x > 100)
		{
			m.unlock();
			break;
		}
		else
		{	
			if((x == 1) || ((x-1) % 5 == 0))
			{
				cout << "thread 1 x = " << x << endl; 
				x++;
			}
			else
			{
				m.unlock();
			}
		}
		
	}
}

void fun2()
{
	m.lock();

	while(1)
	{
	
		if(x > 100)
		{
			m.unlock();
			break;
		}
		else
		{		
			if((x == 2) || ((x-2) % 5 == 0))
			{
				cout << "thread 2 x = " << x << endl; 
				x++;
			}
			else
			{
				m.unlock();
			}
		}
		
	}
}


void fun3()
{
	m.lock();

	while(1)
	{
	
		if(x > 100)
		{
			m.unlock();
			break;
		}
		else
		{		
			if((x == 3) || ((x-3) % 5 == 0))
			{
				cout << "thread 3 x = " << x << endl; 
				x++;
			}
			else
			{
				m.unlock();
			}
		}
		
	}
}


void fun4()
{
	m.lock();

	while(1)
	{
	
		if(x > 100)
		{
			m.unlock();
			break;
		}
		else
		{		
			if((x == 4) || ((x-4) % 5 == 0))
			{
				cout << "thread 4 x = " << x << endl; 
				x++;
			}
			else
			{
				m.unlock();
			}
		}
		
	}
}


void fun5()
{
	m.lock();

	while(1)
	{
	
		if(x > 100)
		{
			m.unlock();
			break;
		}
		else
		{		
			if(x % 5 == 0)	
			{
				cout << "thread 5 x = " << x << endl << endl; 
				x++;
			}
			else
			{
				m.unlock();
			}
		}
		
	}
}
