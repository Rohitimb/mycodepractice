#include<iostream>

using namespace std;

struct s
{
	int x;
	//int y,z;
};

int main()
{
	s ob;
	
	cout << "sizeof(s) = " << sizeof(s) << endl;
	cout << "x = " << &ob.x  << " &s = " << &ob  << endl;
	
	return 0;
}
