#include<iostream>
#include<tuple>

using namespace std;

int main()
{
	tuple <char,int,float> t1;
	tuple <char,int,float> t2;

	cout << "before swapping" << endl;
	t1 = make_tuple('a',10,4.5f);
	cout << get<0>(t1) << " " << get<1>(t1) << " " << get<2>(t1) << endl;	
	
	t2 = make_tuple('A',20,5.4f);
	cout << get<0>(t2) << " " << get<1>(t2) << " " << get<2>(t2) << endl;	
	
	
	cout << "tuple1_size = " << tuple_size<decltype(t1)> :: value << endl;
	cout << "tuple2_size = " << tuple_size<decltype(t2)> :: value << endl;
	
	
	t1.swap(t2);
	cout << "after swapping" << endl;
	cout << get<0>(t1) << " " << get<1>(t1) << " " << get<2>(t1) << endl;	
	cout << get<0>(t2) << " " << get<1>(t2) << " " << get<2>(t2) << endl;	
	
	
	return 0;
}
