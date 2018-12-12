#include<iostream>
#include<unistd.h>
#include<thread>
#include<mutex>

void fun();
int x = 0;

using namespace std;

mutex m;


int main()
{
	thread t1{fun};
	thread t2{fun};

	t1.join();
	t2.join();
	
	return 0;
}


void fun()
{
	while(1)
	{
		m.lock();
		if(x >= 100)
		{
			m.unlock();
			break;
		}
		
		x++;
		
		if(x % 2)	
			cout << "Odd  x = " << x << endl; 
		else 
			cout << "Even x = " << x << endl; 
		
		m.unlock();
	}
}
