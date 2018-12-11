#include<iostream>

using namespace std;

int main()
{
	int *p,*q;
	p = q = nullptr;
		
	p = new int;
	q = new int();
	
	cout << "p = " << p << " q = " << q << endl;
	cout << "*p = " << *p << " *q = " << *q << endl;
	return 0;
}
