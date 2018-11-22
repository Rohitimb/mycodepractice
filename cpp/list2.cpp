#include<iostream>
#include<list>

using namespace std;

int main()
{
	list <int> li;
	
	li.push_front(5);
	li.push_back(10);
	li.push_back(20);
	li.push_back(30);
	li.push_front(3);
	li.push_back(40);
	li.push_front(2);
	li.push_back(50);
	li.push_front(1);	
	
	list<int>::iterator k=li.begin();
	k++;
	k++;
	li.insert(k,1000);

	for(list<int>::iterator i=li.begin();i!=li.end();i++)
	{
		cout << "*i = " << *i << endl; 
	}
	
	return 0;
}
