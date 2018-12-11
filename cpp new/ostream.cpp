#include<iostream>

using namespace std;

class A
{
	private:
		int x,y;
	public:
		A():x(10),y(20)
		{
		}
		
		void print()	
		{
			cout << __func__ << " " << endl;
			cout << "x = " << x << " y = " << y << endl;
		}
		friend ostream& operator << (ostream&,A&);
	
};

ostream& operator << (ostream& out,A& ob)
{
	out << "x = " << ob.x << " y = " << ob.y <<  endl;
	return out;
}
	
int main()
{
	A obj;
	cout << obj << endl;
	
	return 0;
}
