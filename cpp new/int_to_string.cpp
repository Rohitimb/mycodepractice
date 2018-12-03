#include<iostream>

using namespace std;

int main()
{
	int i = 10;
	
	string s;
	s = to_string(i);

	cout << "i = " << i << " s = "  << s << " string length = " << s.length()<< endl;
	
	return 0;
}
