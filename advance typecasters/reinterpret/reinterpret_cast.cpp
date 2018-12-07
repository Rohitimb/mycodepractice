#include<iostream>

using namespace std;

class A
{
	private:
		int x,y;
	public:
		A():x(10),y(20){}
		void printa(){cout << "x = " << x << " y = " << y << endl;}
};

class B
{
	private:	
		int c,d;
	public:
		B():c(55),d(77){}
		void printb(){cout << "c = " << c << " d = " << d << endl;}
};
int main()
{
	A *a = new A;
	B *b;
	
	b = reinterpret_cast<B*>(a);
	b->printb();
	
	delete b;	

	return 0;
}
