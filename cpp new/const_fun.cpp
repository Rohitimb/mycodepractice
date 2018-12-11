#include<iostream>

using namespace std;

class A
{
	private:
		int x;

	public:
		A():x(10){}
	
		void print() const 
		{	
			//x = 20; /*not allowed since int const function*/
			cout << "const x = " << this->x << endl;
		}
		
		void print() 
		{	
			//x = 20; /*not allowed since int const function*/
			cout << "x = " << this->x << endl;
		}
};

int main()
{
	const A ob;
	A ob2;

	ob.print();
	ob2.print();
	
	
	return 0;
}
