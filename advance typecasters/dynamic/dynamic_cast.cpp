#include<iostream>

using namespace std;

class B
{
	public:
		//void fun(){cout << "B" << endl;}
		virtual ~B(){}
};

class D:public B
{
	public:
		void fun(){cout << "D" << endl;}
};
int main()
{
		
	B *b = new D();//upcasting
    D *d = dynamic_cast<D*>(b); //downcasting
	d->fun();
		
	return 0;
}
