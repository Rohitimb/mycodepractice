#include<iostream>

using namespace std;

struct A
{
	int i;
	int m;
	float f;
	double d;
	char c;
	bool b;
};

int main()
{
	A var = {10,20,45.6f,56.44,'A',true};
	
	cout << var.i << " "<< var.m << " " << var.f << " " << var.d << " " << var.c << " " << var.b << endl;
	
	int *p = reinterpret_cast<int*>(&var);
	cout << *p << endl;
	p++;
	
	cout << *p << endl;
	p++;
		
	float *f = reinterpret_cast<float*>(p);
	cout << *f << endl;
	f++;

	double *d = reinterpret_cast<double*>(f);
	cout << " : " << *d << endl;
	d++;

	char *c = reinterpret_cast<char*>(d);
	cout << *c << endl;
	c++;

	bool *b = reinterpret_cast<bool*>(c);
	cout << *b << endl;

	return 0;
}
