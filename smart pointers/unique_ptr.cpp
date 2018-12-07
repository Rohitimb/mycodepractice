#include<iostream>
#include<memory>

using namespace std;

class A
{
	private:
		int x;
	public:
		A():x(10){}
		void print(){
			cout << "x - " << x << endl;
		}
};

int main()
{
	unique_ptr<A>p1(new A);
	p1->print();

	cout << "p1 - " << p1.get() << endl;
	
	//unique_ptr<A>p2(p1);/*not allowed*/
	
	unique_ptr<A> p2 = move(p1);
	
	cout << "p1 - " << p1.get() << endl;
	cout << "p2 - " << p2.get() << endl;
	
	unique_ptr<A> p3;
	p3  = move(p2);
	
	cout << "p1 - " << p1.get() << endl;
	cout << "p2 - " << p2.get() << endl;
	cout << "p3 - " << p3.get() << endl;
	
	
		
	return 0;
}
