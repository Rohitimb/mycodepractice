#include<iostream>

using namespace std;

int main()
{
	int  x = 10;
	
	void *v = static_cast<void*>(&x);
	cout << "&x = " << &x << " v = " << v << " *v = " <<  *(int*)v << endl; 
	
	int *i = static_cast<int*>(v);
	cout << "v = " << v << " i = " << i << " *i = " <<  *i << endl; 
	
	
	return 0;
}
