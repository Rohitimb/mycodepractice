#include<iostream>
#include<memory>

using namespace std;

class A
{
	private:
		int x;
	public:
		A():x(10){}
		void print()
		{
			cout << "x - " << x << endl;
		}
		~A()
		{
			cout << "destructor" << endl;
		}
};

int main()
{
	auto_ptr<A>p1(new A);
	p1->print();
	
	cout << "p1 = "<< p1.get() << endl;
	
	auto_ptr<A>p2(p1);//p2 own resource p1 is null now
	
	cout << "p1 = "<< p1.get() << endl;//p1 is null now
	cout << "p2 = "<< p2.get() << endl;
	
	return 0;
}
