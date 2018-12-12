#include<iostream>
#include<forward_list>

using namespace std;

int main()
{
	forward_list<int> f1;

	f1.assign({1,55,77,88});
	
	for(auto &i:f1)
		cout << i <<endl;
	
	string str = "LotToLearn";

	for(char c:"LotToLearn")//can pass str directly
		cout << c << " ";
	cout << endl;
	
	for(int c: {4,5,6,7,8,9})
		cout << c << " ";
	cout << endl;
	
	int a[] = {4,3,2,1,0};

	for(int c:a)
		cout << c << " ";
	cout << endl;
	
	return 0;
}
