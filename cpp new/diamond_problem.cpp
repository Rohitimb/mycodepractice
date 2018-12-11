#include<iostream>

using namespace std;

class A
{
	public:
		void fun()
		{
			cout  << "fun - A" << endl;
		}
};

class B: virtual public A
//class B: public A
{
};

class C : virtual public A
//class C : public A
{
};

class D : public B, public C
{
};

int main()
{
	D d;
	d.fun();
		
	return 0;
}
