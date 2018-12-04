#include<iostream>
#include<tuple>

using namespace std;

int main()
{
	tuple <char,int,float> t;

	t = make_tuple('a',10,4.5f);
	cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;	
	
	get<0>(t) = 'b';
	get<1>(t) = 40+20;
	get<2>(t) = 56.7;

	cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;	
	
	cout << "tuple_size = " << tuple_size<decltype(t)> :: value << endl;
	
	return 0;
}
