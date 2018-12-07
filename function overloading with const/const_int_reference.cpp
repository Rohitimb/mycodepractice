#include<iostream>

using namespace std;

void print(int &i);
void print(const int &i);

int main()
{
	int a = 49;
	const int b = 10;
	
	print(a);	
	print(b);
		
	return 0;
}

void print(int &i)
{
	cout << "print " << i << endl;
}

void print(const int &i)
{
	cout << "print " << i << endl;
}
