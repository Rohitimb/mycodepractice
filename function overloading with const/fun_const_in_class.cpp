#include<iostream>

using namespace std;

class A
{
	public:
		void print();
		void print() const;
};

int main()
{
	A ob1;
	const A ob2;
	
	ob1.print();
	ob2.print();

	return 0;
}

void A :: print()
{
	cout << "print" << endl;
}

void A :: print() const
{
	cout << "const print" << endl;
}
