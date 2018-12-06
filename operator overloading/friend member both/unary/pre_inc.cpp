#include<iostream>
#define MEMBER

using namespace std;

class A
{
	private:
		int x,y;
	public:
		A();
		void print();
		#ifdef MEMBER
			void operator ++();
		#else
			friend void operator ++(A&);
		#endif
};

A :: A():x(10),y(20)
{
		cout << "default constructor" << endl;
}

void A :: print()
{
		cout << "x = " << x << " y = " << y << endl;
}
#ifdef MEMBER
void A :: operator ++()
{
		++x;
		++y;
}
#else
void operator ++(A& ob)
{
		++ob.x;
		++ob.y;
}
#endif
int main()
{
	A ob;
		
	ob.print();	
	++ob;	
	
	ob.print();	
	return 0;
}
