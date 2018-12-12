#include<iostream>
#include<unistd.h>
#include<thread>

using namespace std;

void fun1(int x);
void fun2(double y);

int main()
{
	thread t1{bind(fun1,10)};
	thread t2{bind(fun2,22.5)};

	t1.join();
	t2.join();
	
	return 0;
}


void fun1(int x)
{
    while(1)
    {
        usleep(50000);
        cout << "thread fun1 x = " << x << endl;
    }
}

void fun2(double y)
{
    while(1)
    {
        usleep(50000);
        cout << "thread fun2 y = " << y << endl;
    }
}



