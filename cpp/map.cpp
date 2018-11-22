#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {

	map<string, int> ages;

	ages["Mike"] = 40;
	ages["Raj"] = 20;
	ages["Vicky"] = 30;
	ages["Mike"] = 70;

	ages.insert(make_pair("Peter", 100));

	cout << ages["Raj"] << endl;

	if(ages.find("Vicky") != ages.end()) {
		cout << "Found Vicky" << endl;
	}
	else {
		cout << "Key not found." << endl;
	}

	for(map<string, int>::iterator it = ages.begin(); it != ages.end(); it++) {
		pair<string, int> age = *it;

		cout << "NAME = " << age.first << ": "  << " Age = " << age.second << endl;
	}

	for(map<string, int>::iterator it = ages.begin(); it != ages.end(); it++) {
			cout << it->first << ": " << it->second << endl;
		}


	return 0;
}
