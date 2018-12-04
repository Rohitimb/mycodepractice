#include<iostream>
#include<tuple>

using namespace std;

int main()
{
	char c;	
	int i;
	float f;
	
	tuple <char,int,float> t;

	t = make_tuple('a',10,4.5f);
	cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;	
	
	
	
	tie(c,i,f) = t;
	cout << "Unpacked values are\n";
	cout << c << " " << i << " " << f << endl;	
	
	
	tie(c,ignore,f) = t;
	cout << "Unpacked values are\n";
	cout << c << " " << i << " " << f << endl;	
	
	cout << "tuple_size = " << tuple_size<decltype(t)> :: value << endl;
	
	return 0;
}
