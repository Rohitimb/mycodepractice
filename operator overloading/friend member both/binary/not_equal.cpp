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
			bool operator != (const A&);
		#else
			friend bool operator != (const A&,const A&);
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
bool A ::  operator != (const A& ob)
{
	if((x != ob.x) && (y != ob.y))
		return true;
	else
		return false;
}
#else
bool operator != (const A& ob1,const A& ob2)
{	
	if((ob1.x != ob2.x) && (ob1.y != ob2.y))
		return true;
	else
		return false;
}
#endif
int main()
{
	bool var;
	A ob1(10,20);	
	A ob2(10,0);
	A ob3(0,20);
	A ob4(10,20);
	A ob5(11,22);
	
	ob1.print();
	ob2.print();
	ob3.print();
	ob4.print();
	ob5.print();
	
	var = ob1 != ob2;//ob1.operator &&(ob2) as member function call
	cout << "var = " << var << endl;
	
	var = ob1 != ob3;
	cout << "var = " << var << endl;

	var = ob1 != ob4;
	cout << "var = " << var << endl;
	
	var = ob1 != ob5;
	cout << "var = " << var << endl;
	return 0;
}
