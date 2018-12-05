#include<iostream>

using namespace std;

class A
{
	private:
		int x,y;
	public:
		A():x(10),y(20)
		{
			cout << "default constructor" << endl;
		}
		A(int i,int j):x(i),y(i)
		{
			cout << "parameterized constructor" << endl;
		}
		~A()
		{
			cout << "destructor" << endl;
		}
	
		friend ostream& operator << (ostream& out, A& ob);

		void print()
		{
			cout << "x = " << x << " y = " << y << endl;
		}
};

ostream& operator << (ostream& out, A& ob)
{
	cout << "x = " << ob.x << " y = " << ob.y << endl;
	return out;
}

int main()
{
	A ob,ob2(11,22);
	
	cout <<"using normal function" << endl;
	ob.print();
		
	cout <<"using overloaded << operator" << endl;
	cout << ob << endl;
	cout << ob2 << endl;
	
	return 0;
}
