#include<iostream>

using namespace std;

class A
{
	private:
		int x;
	public:
		A():x(10){}
		explicit A(int a):x(a){}
		void print(){cout << "x = " << x << endl;}
};

int main()
{
	int val;
	A ob(54);
	
	//ob = 55;
	ob = static_cast<A>(66);

	ob.print();
	
	return 0;
}
