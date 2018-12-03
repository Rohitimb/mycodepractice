#include<iostream>
#include <functional> 

using namespace std;

using namespace std::placeholders;

void fun(int a,int b, int c)
{
	cout << "result = " << a -  b  - c << endl;
}

int main()
{	
	cout << "bind functions" << endl;
	
	auto func = bind(fun,_3,_2,_1);
	cout << "bind function" << endl;
	func(30,20,10);
	
	cout << "normal function" << endl;
	fun(30,20,10);	
	
	return 0;
}
