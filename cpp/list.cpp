#include <iostream>
#include <list>

using namespace std;

int main() 
{
	list<int> numbers;

	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(3);
	numbers.push_front(0);
	//0 1 2 3

	list<int>::iterator it = numbers.begin();
	it++;
	numbers.insert(it, 100);
	
	list<int>::iterator eraseIt = numbers.begin();
	eraseIt++;
	eraseIt = numbers.erase(eraseIt);

	cout << "Size = " << numbers.size() << endl;
	for(list<int>::iterator it=numbers.begin(); it != numbers.end(); it++) {
		cout << *it << endl;
	}

	return 0;
}
