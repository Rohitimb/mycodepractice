#include<iostream>
#include<math.h>

using namespace std;

int main()
{
	double x = 4.55;
	
	if(isnan(x))
		cout << "Not a number" << endl;
	else
		cout << "is a number" << endl;
	return 0;
}
