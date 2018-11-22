#include<iostream>
#include<map>
#include<string>

using namespace std;

int main()
{
	map<string,int> m;
	
	m["Apple"] = 1;
	m["BlackBerry"] = 2;
	m["China"] = 3;
	m["Fly"] = 6;
	

	m.insert(make_pair("G5",7));

	cout << "auto" << endl;
	for(auto i=m.begin();i!=m.end();i++)
	{
		cout << i->first << " : " << i->second << endl;
	}
	
	for(map<string,int>::iterator i=m.begin();i!=m.end();i++)
	{
		cout << i->first << " : " << i->second << endl;
	}
	
	cout << "-------------------" << endl;
	
	for(map<string,int>::iterator i=m.begin();i!=m.end();i++)
	{
		pair<string,int> v = *i;

		cout << v.first << " : " << v.second << endl;
	}
	
	if(m.find("") != m.end())
	{
		cout << "found" << endl;
	}
	else
	{
		cout << "not found " << endl;
	}
	
	return 0;
}
