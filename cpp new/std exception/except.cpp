#include<iostream>
#include<exception>

using namespace std;

class myexcep : public std::exception
{
	virtual const char* what() const throw()
	{
		return "hello there, this is an exception";
	}
};

int main()
{
	int *p = nullptr;
	try
	{	
		p = new int[343345645645644];
		//throw myexcep();
	}
	catch(exception &e)
	{
		cout << e.what() << endl;
	}
	
	return 0;
}
