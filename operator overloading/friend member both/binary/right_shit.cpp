#include<iostream>
//#define MEMBER
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
			A operator >> (const A&);
		#else
			friend A operator >> (const A&,const A&);
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
A A ::  operator >> (const A& ob)
{
	A temp;
	temp.x = x >> ob.x;
	temp.y = y >> ob.y;
return temp;
}
#else
A operator >> (const A& ob1,const A& ob2)
{	
	A temp;
	temp.x = ob1.x >> ob2.x;
	temp.y = ob1.y >> ob2.y;
	return temp;
}
#endif
int main()
{
	A ob1(32,2048);	
	A ob2(4,8);
	A ob3;
	
	ob3 = ob1 >> ob2;//ob1.operator >> (ob2) as member function call

	ob1.print();
	ob2.print();
	ob3.print();
	
	return 0;
}
