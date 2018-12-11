#include<iostream>
#include<cstring>

using namespace std;

class A
{
	private:
		const char *p;
		
		A(const A&) = delete;  // prevent copying
 	 	A& operator=(const A&) = delete;
	public:
		A():p("Hello World\n"){}	
		void print()
		{
			cout << "string = " << p << endl;
		}
		~A()
		{
			//delete p;
			cout << "dtor called" << endl;
		}
};
int main()
{
	A ob1;
	ob1.print();
	//A ob2 = ob1;
	//ob2.print();

	return 0;
}
