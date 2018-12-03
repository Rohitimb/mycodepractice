#include<iostream>

using namespace std;

class A
{
	private:
		A(){}
	public:
	static bool flag;
	static A* getinstance();
	
};

bool A :: flag = false;

A* A:: getinstance()
{
	static A *ob;
	if(!flag)
	{
		ob = new A();
		flag = true;
		return ob;
	}
	else
	{
		return ob;
	}
}

int main()
{
	A *ob1,*ob2;
	ob1 = A::getinstance();
	ob2 = A::getinstance();
	
	cout << ob1 << " " << ob2 << endl;
	
	return 0;
}
