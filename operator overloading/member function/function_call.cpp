#include<iostream>

using namespace std;

class A
{
	private:
		int x,y;
	public:
		A();
		A(int,int);
		~A();
		void print();
		void operator () (int,int);
};

A :: A():x(10),y(20)
{
		cout << "default constructor" << endl;
}

A :: A(int i,int j):x(i),y(i)
{
		cout << "parameterized constructor" << endl;
}

A ::~A()
{
		cout << "destructor" << endl;
}

void A :: print()
{
		cout << "x = " << x << " y = " << y << endl;
}

void A :: operator () (int i,int j)
{
		x=i,y=j;
}


int main()
{
	A ob,ob2;
	ob.print();
	
	ob2(44,66);//ob.operator()(int,int)
	
	ob2.print();
	
	return 0;
}
