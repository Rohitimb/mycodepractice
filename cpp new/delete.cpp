#include<iostream>

using namespace std;

int main()
{
	int *p;
	p = nullptr;
	
	p = new int;
	delete p;
	p = nullptr;
	delete p;
	delete p;
	delete p;
	delete p;
	delete p;

	cout << "deleted"<< endl;;
	return 0;
}
