#include<iostream>

using namespace std;

int main()
{
	char *cp = new char('A');

	int *ip = const_cast<int*>(cp);/*not allowed*/
	cout << *ip << endl;
	
	return 0;
}
