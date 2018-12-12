#include<iostream>
#include<forward_list>

using namespace std;

int main()
{
	forward_list<int> f1;

	f1.assign({1,55,77,88});
	
	for(auto i = f1.begin();i != f1.end();i++)
		cout << *i << endl;
	
	return 0;
}
