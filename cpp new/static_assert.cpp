#include<iostream>

using namespace std;

int main()
{
	const int x = 100,y = 20;

	static_assert(x < y,"should be same");//condition has to be true, orelse compilation will not be successful
	return 0;
}
