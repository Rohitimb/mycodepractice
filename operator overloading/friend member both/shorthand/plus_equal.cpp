#include<iostream>
#define MEMBER
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
		#ifdef MEMBER
			A operator += (const A&);
		#else
			friend A operator += (A&,const A&);
		#endif
};

A :: A():x(10),y(20)
{
		cout << "default constructor" << endl;
}
A :: A(int i,int j):x(i),y(j)
{
		cout << "parameterized constructor" << endl;
}
A :: ~A()
{
		cout << "destructor" << endl;
}

void A :: print()
{
		cout << "x = " << x << " y = " << y << endl;
}

#ifdef MEMBER
A A ::  operator += (const A& ob)
{
	x += ob.x;
	y += ob.y;
	return *this;
}
#else
A operator += (A& ob1,const A& ob2)
{	
	ob1.x += ob2.x;
	ob1.y += ob2.y;
	return ob1;
}
#endif
int main()
{
	A ob1(10,20);	
	A ob2(20,10);
	
	ob1.print();

	ob1 += ob2;

	ob1.print();
	ob2.print();
	
	return 0;
}
