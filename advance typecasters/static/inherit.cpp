#include<iostream>

using namespace std;

class B
{
	public:
	void fun(){cout << " in base" << endl;}
};

class D:public B//not allowed with private inherit for static type casting
{
	public:
	void fun(){cout << " in derived" << endl;}
};

int main()
{	
	D d;
	
	B *b1 = (D*)(&d);
	B *b2 = static_cast<B*>(&d);
	
	b1->fun();
	b2->fun();
	
	return 0;
}
