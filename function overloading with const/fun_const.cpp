#include<iostream>

using namespace std;

/*program will generate an error, multiple definition of print function*/
int main()
{
	print();
	return 0;
}

void print()
{
	cout << "print" << endl;
}

void print() const
{
	cout << "const print" << endl;
}
