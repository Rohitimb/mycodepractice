#include<iostream>

using namespace std;

void print(char*);
void print(const char*);

int main()
{
	char a[] = "LotToLearn";
	const char b[] = "StatNowUpFDI";
	
	print(a);
	print(b);
		
	return 0;
}

void print(char* i)
{
	cout << "print " << i << endl;
}

void print(const char* i)
{
	cout << "print " << i << endl;
}
