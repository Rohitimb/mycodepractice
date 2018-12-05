#include<iostream>

using namespace std;

class A
{
	private:
		int x,y;
	public:
		A():x(10),y(20)
		{
			cout << "default constructor" << endl;
		}
		A(int i,int j):x(i),y(i)
		{
			cout << "parameterized constructor" << endl;
		}
		~A()
		{
			cout << "destructor" << endl;
		}
		void print()
		{
			cout << "x = " << x << " y = " << y << endl;
		}
		
		void operator () (int i,int j)
		{
			x=i,y=j;
		}
};

int main()
{
	A ob,ob2;
	ob.print();
	
	ob2(44,66);//ob.operator()(int,int)
	
	ob2.print();
	
	return 0;
}
