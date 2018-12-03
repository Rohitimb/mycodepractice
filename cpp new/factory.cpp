#include<iostream>

using namespace std;

enum mtype{IPHONE,BLACKBERRY,MI,SAMSUNG};

class mobile
{
	public:
		virtual void printBrandName() = 0;
		static mobile* createobj(mtype);
};

class iphone : public mobile
{
	public:
		void printBrandName()
		{
			cout << "iPhone SE" << endl;
		}
};
	
class blackberry : public mobile
{
	public:
		void printBrandName()
		{
			cout << "Blackberry Z10" << endl;
		}
};

mobile* mobile::createobj(mtype t)
{
	if(t == IPHONE)
	{
		return new iphone();	
	}
	else if(t == BLACKBERRY)
	{
		return new blackberry();
	}
	else
			return NULL;
}

class client
{
	private:
		mobile *pMobilePtr;
	public:
		client()
		{
				mtype type = BLACKBERRY;
				pMobilePtr = mobile:: createobj(type);
		}
	
		mobile* getMobile()
		{
				return pMobilePtr;
		}

		~client()
		{
			cout << "freeing the memory" << endl;
			if(pMobilePtr)
			{
				delete [] pMobilePtr;
				pMobilePtr = NULL;
			}
		}	
};

int main()
{
	client *obj= new client();
	mobile *ob = obj->getMobile();
	ob->printBrandName();
	
	return 0;
}
