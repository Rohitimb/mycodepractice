#include<iostream>
#include<functional>

using namespace std;
using namespace placeholders;

class worker
{
	public:
		void work(string str,int x)
		{
			cout << "str = " << str << " x = " << x <<  endl; 
		}
};

int main()
{
	worker *pwork = nullptr;
	//worker work;
	
	auto f1 = std::bind(&worker::work,pwork,"f1",21);
	f1();//pwork->work("f1",21);

	auto f2 = std::bind(&worker::work,pwork,"f2",_1);
	f2(22);//pwork->work("f2",22);
		
	auto f3 = std::bind(&worker::work,pwork,_1,23);
	f3("f3");//pwork->work("f3",23);
	
	auto f4 = std::bind(&worker::work,pwork,_1,_2);
	f4("f4",24);//pwork->work("f4",24);
		
	auto f5 = std::bind(&worker::work,pwork,_2,_1);
	f5(25,"f5");//pwork->work("f5",25);
	
	//auto f6 = std::bind( &worker::work, pwork,"f6",26);
	//Callback<string,int> cb( f6 );

	Callback<string,uint32_t> cb(bind(&worker::work, pwork,"f7",37) );
	return 0;
}
