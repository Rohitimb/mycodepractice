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
		void operator ++(int);
		#else
		friend void operator ++(A&,int);
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
void A:: operator ++(int i)
{
		x++;
		y++;
}
#else
void operator ++(A& ob,int i)
{
	ob.x++;
	ob.y++;

}
#endif

int main()
{
	A ob;
		
	ob.print();	
	ob++;	
	
	ob.print();	
	return 0;
}
