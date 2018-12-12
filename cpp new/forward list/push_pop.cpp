#include<iostream>
#include<forward_list>

using namespace std;

int main()
{
	forward_list <int>v = {1,2,3,4};

	v.assign({55,65,7,8});// now list contains 55,65,7,8
	v.assign({5,6,7,8});//now list contains 5,6,7,8
	
	for(auto &i:v)
		cout << i << " ";
	
	v.push_front(1);
	cout << "after adding" << endl;
	for(auto &i:v)
		cout << i << " ";
	cout << endl;

	v.push_front(4);
	cout << "after adding" << endl;
	for(auto &i:v)
		cout << i << " ";
	cout << endl;
	
	v.emplace_front(3);
	cout << "after adding" << endl;
	for(auto &i:v)
		cout << i << " ";
	cout << endl;
	
	v.pop_front();
	cout << "after popping" << endl;
	for(auto &i:v)
		cout << i << " ";
	cout << endl;

	v.pop_front();
	cout << "after popping" << endl;
	for(auto &i:v)
		cout << i << " ";

	cout << endl;
	return 0;
}
