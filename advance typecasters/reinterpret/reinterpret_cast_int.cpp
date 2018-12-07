#include<iostream>

using namespace std;

int main()
{
	char *c = new char('A');
	char d = 'a';
	int *p;
	p = reinterpret_cast<int*>(c);
	cout << *p << endl;

	char *m = &d;
	cout << "*m = " << *m << endl;
	
	p = reinterpret_cast<int*>(m);
	cout << *p << endl;
	
	return 0;
}
