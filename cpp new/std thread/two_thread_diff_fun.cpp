#include<iostream>
#include<unistd.h>
#include<thread>
#include<mutex>


void fun1();
void fun2();

int x = 1;

using namespace std;

mutex m;

int main()
{
	thread t1{fun1};
	thread t2{fun2};

	t1.join();
	t2.join();
	
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
            if(x % 2)
            {
                cout << "Odd  x = " << x << endl;
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

            if(!(x % 2))
            {
                cout << "Even x = " << x << endl;
                x++;
            }
            else
            {
                m.unlock();
            }
        }

    }
}

