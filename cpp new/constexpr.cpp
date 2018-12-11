#include<iostream>

using namespace std;

int sum(int x,int y)
{
	return (x+y);
}

int main()
{
	constexpr int i = 10;
	const int j = 3;
	cout << "i = " << i << " j = " << j <<endl;
	
	//i = 20;
	//cout << "i = " << i << " j = " << j <<endl;
	cout << "sum = " << sum(10,20) << endl;; 
		
	return 0;
}
