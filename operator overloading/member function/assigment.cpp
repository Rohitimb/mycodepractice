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
		void operator = (A&);
		void print();
};

A :: A():x(10),y(20)
{
		cout << "default constructor" << endl;
}

A ::A(int i,int j):x(i),y(j)
{
		cout << "parameterized constructor" << endl;
}

A :: ~A()
{
		cout << "destructor" << endl;
}

void A :: operator = (A& ob)
{
		cout << "operator = " << endl;
		x = ob.x,y=ob.y;
}

void A ::print()
{
		cout << "x = " << x << " y = " << y << endl;
}

int main()
{
	A ob(15,25);	
	A ob2;

	ob.print();
	ob2.print();
	
	ob2 = ob;
	
	ob.print();
	ob2.print();
	
	return 0;
}
