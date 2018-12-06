#include<iostream>
//#define MEMBER

using namespace std;

class A
{
	private:
		int x,y;
	public:
		A();
		void print();
		#ifdef MEMBER
			A operator ~();
		#else
			friend A operator ~(A&);
		#endif
};

A :: A():x(1),y(2)
{
	//cout << "default constructor" << endl;
}
		
void A :: print()
{
	cout << "x = " << x << " y = " << y << endl;
}

#ifdef MEMBER
A A :: operator ~()
{
	x = ~x;
	y = ~y;
	return *this;
}
#else
A operator ~(A& ob)
{
	ob.x = ~ob.x;
	ob.y = ~ob.y;
	return ob;
}

#endif
int main()
{
	A ob,ob2,ob3;
	cout << "Before" << endl;
	ob.print();	
	ob2.print();	
	~ob;
	ob2 = ~ob3;
	
	cout << "After" << endl;
	ob.print();	
	ob2.print();	
	ob3.print();	
	return 0;
}
