#include<iostream>
#include<string.h>

using namespace std;

class A
{
	private:
		int *p,size;
	public:
		A(): p(new int[5]),size(5)
		{
			memset(p,0x00,sizeof(int)*size);
			cout << "default constructor" << endl;
		}
		A(int *a,int s)
		{
			int i;
			p = new int[s];
			size = s;
			for(i=0;i<size;i++)
			{
				p[i] = a[i];
			}
			cout << "parameterized constructor" << endl;
		}
		~A()
		{
			delete []p;
			p = nullptr;
			cout << "destructor" << endl;
		}
		void print()
		{
			for(int i=0;i<size;i++)
			{
				cout << "p[" << i << "] = " << p[i] << endl;
			}
		}
		int& operator [] (int index)
		{
			if(index >= size)
			{
				cout << "invalid position" << endl;
				exit(0);
			}
			return p[index];
		}
};

int main()
{
	int i;
	int a[5] = {10,20,20,40,50};
	int size = sizeof(a)/sizeof(a[0]);
	
	A ob(a,size);	
	ob.print();
	
	ob[1] = 6;//ob.operator[](1)
	ob.print();
	
	for(i=0;i<size;i++)
	{
		cout << "p[" << i << "] = " << ob[i] << endl;
	}
	
	return 0;
}
