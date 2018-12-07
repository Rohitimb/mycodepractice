#include<iostream>

using namespace std;

int cal(int* p)
{
	*p = (*p)*2;
	return *p;
}

int main()
{
	int i = 10;
	//const int i = 10;
	int k;
	
	const int *ptr = &i;
	int *ptr1 = const_cast<int*>(ptr);
	k = cal(ptr1);
	
	cout << "k = " << k << " i = " << i << endl;
}

