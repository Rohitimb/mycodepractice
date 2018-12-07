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
		~A(){cout << "destructor" << endl;}
};

int main()
{
	shared_ptr<A>p1(new A);
	p1->print();

	cout << "p1 - " << p1.get()  << " count - " << p1.use_count()<< endl;
	
	shared_ptr<A> p2(p1);
	
	cout << "p1 - " << p1.get()  << " count - " << p1.use_count()<< endl;
	cout << "p2 - " << p2.get()  << " count - " << p2.use_count()<< endl;
	
	
	shared_ptr<A> p3(p1);
	
	cout << "p1 - " << p1.get()  << " count - " << p1.use_count()<< endl;
	cout << "p2 - " << p2.get()  << " count - " << p2.use_count()<< endl;
	cout << "p3 - " << p3.get()  << " count - " << p3.use_count()<< endl;
	
	p1.reset();
	cout << "p1 - " << p1.get()  << " count - " << p1.use_count()<< endl;
	cout << "p2 - " << p2.get()  << " count - " << p2.use_count()<< endl;
	cout << "p3 - " << p3.get()  << " count - " << p3.use_count()<< endl;
	
	p2.reset();
	cout << "p1 - " << p1.get()  << " count - " << p1.use_count()<< endl;
	cout << "p2 - " << p2.get()  << " count - " << p2.use_count()<< endl;
	cout << "p3 - " << p3.get()  << " count - " << p3.use_count()<< endl;
	
	p3.reset();
	cout << "p1 - " << p1.get()  << " count - " << p1.use_count()<< endl;
	cout << "p2 - " << p2.get()  << " count - " << p2.use_count()<< endl;
	cout << "p3 - " << p3.get()  << " count - " << p3.use_count()<< endl;
	return 0;
}
