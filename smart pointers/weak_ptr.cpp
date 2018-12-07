#include <iostream>
#include <memory>

using namespace std;

class A
{
	private:
		int x;
	public:
		A():x(10)
		{
		}
		
		void set(int y)
		{
			x=y;
		}
		
		int get()
		{
			return x;
		}
		
		void print()
		{
			cout << "x - " << x << endl;
		}
};

int main()
{
    shared_ptr<A> sptr;

    sptr.reset(new A);
	sptr->set(20);
	sptr->print();

    std::weak_ptr<A> weak1 = sptr;

    // deletes managed object, acquires new pointer
    sptr.reset(new A);
	sptr->set(50);
	sptr->print();

	weak_ptr<A> weak2 = sptr;	

    if(auto tmp = weak1.lock())
        cout << "x = " <<tmp->get() << endl;
    else
		cout << "weak1 is expired" << endl;
  
    if(auto tmp = weak2.lock())
        cout << "x = " <<tmp->get() << endl;
    else
        cout << "weak2 is expired" << endl;
}
