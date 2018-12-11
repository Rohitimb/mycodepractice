#include<iostream>

using namespace std;

class A{
	private:
		const int x;
	public:
		A():x(10)
		{
			//x = 10; /*not allowed since its const can not be assigned, but can be initialized*/
		}
		void print()
		{
			cout << "x = " << x << endl;
		}
};

int main()
{
	A ob;
	ob.print();
	return 0;
}
