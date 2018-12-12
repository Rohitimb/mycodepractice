#include<iostream>
#include<unistd.h>
#include<thread>

using namespace std;

void fun1();
void fun2();

int main()
{
	std::thread t1{fun1};
	std::thread t2{fun2};

	t1.join();
	t2.join();
	
	return 0;
}



void fun1()
{
    while(1)
    {
        usleep(50000);
        cout << "thread fun1 " << endl;
    }
}

void fun2()
{
    while(1)
    {
        usleep(50000);
        cout << "thread fun2 " << endl;
    }
}


