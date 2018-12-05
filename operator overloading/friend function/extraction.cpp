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
		A(int i,int j):x(i),y(j)
		{
			cout << "parameterized constructor" << endl;
		}
		~A()
		{
			cout << "destructor" << endl;
		}
	
		friend istream& operator >> (istream& out, A& ob);

		void print()
		{
			cout << "x = " << x << " y = " << y << endl;
		}
};

istream& operator >> (istream& in, A& ob)
{
	int x,y;
	in >> x >> y;
	ob.x = x,ob.y = y;
	return in;
}

int main()
{
	int a,b;
	cout << "Enter two values = ";
	cin >> a >> b;
	
	A ob(a,b);
	cout <<"using normal function" << endl;
	ob.print();
		
	cout << "Enter two values = ";	
	cin >> ob;
	
	cout <<"using overloaded >> operator" << endl;
	ob.print();
	return 0;
}
