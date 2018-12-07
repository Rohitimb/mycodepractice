#include<iostream>

using namespace std;

class A
{
	private:
		int x;// allowed in const function but casting has to be done
		//const int x; not allowed to change in const function
	public:
		//A():x(10){}
		A(int a):x(a){}
		void print2()
		{
			cout << "x - " << x << endl;
		}
		void print() const
		{			
			(const_cast<A*>(this))->x = 5;
			cout << "const"<< endl;
			cout << "x = " << x << endl;;
		}
};

int main()
{
	A ob(15);
	ob.print();
	return 0;
}
