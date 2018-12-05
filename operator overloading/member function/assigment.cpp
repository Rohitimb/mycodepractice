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
		A(int i,int j):x(i),y(j)
		{
			cout << "parameterized constructor" << endl;
		}
		~A()
		{
			cout << "destructor" << endl;
		}
		void operator = (A& ob)
		{
			cout << "operator = " << endl;
			x = ob.x,y=ob.y;
		}
		void print()
		{
			cout << "x = " << x << " y = " << y << endl;
		}
};

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
