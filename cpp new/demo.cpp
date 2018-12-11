#include<iostream>
using namespace std;
class A {
	int b;
		public :
				A(){
				cout << "default constructor" << endl;
				} 
				 A(int a):b(a){
					cout << "parameterized constructor" << endl;				
				}
			};
int main ()
{
		A a1;
		a1 =  5;

		return 0;
}
