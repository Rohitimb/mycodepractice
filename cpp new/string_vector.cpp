#include<vector>
#include<string>
#include<iostream>
#include<algorithm>

using namespace std;

int main() 
{
		cout << "enter some whitespace-separated words:\n";
		vector<string> v;
		string s;
		while (cin>>s) v.push_back(s);
		sort(v.begin(),v.end());
		string cat;
		for (auto & str : v) cat += str+"+";
		cout << cat << '\n';
}
