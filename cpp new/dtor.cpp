#include<iostream>

using namespace std;

class A
{
	private:
		int *p;
	public:
		A():p(new int(55))
		{
			cout << "ctor" << endl;
		}
		void print()
		{
			cout << "*p = " << *p <<  endl;
		}
		~A()
		{
			delete p;
			p = nullptr;
			cout << "dtor" << endl;
		}
};

int main()
{
	#if 1
	A *ob = new A();
	ob->print();
	delete ob;// to call destructor
	#else
	A ob2;
	ob2.print();
	#endif
	
	return 0;
}
