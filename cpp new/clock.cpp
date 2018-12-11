#include<iostream>
#include<ratio>
#include<chrono>

using namespace std;

int main()
{
	auto t = steady_clock::now();
	// do something	
	auto d = steady_clock::now() - t;
	// something took d time units
	
	//cout << "t = " << t << " d = " << d << endl;
	return 0;
}
