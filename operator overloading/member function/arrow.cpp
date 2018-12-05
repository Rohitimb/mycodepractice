#include<iostream>
#include<vector>

using namespace std;

class B
{
	private:
		int p,q;
	public:
		B():p(10),q(20)
		{
			
		}
		void print()
		{
			cout << "p = "<< p << " q = " << q << endl;					

		}
};

class FtrB
{
	vector<B*> a;

	public:
		void add(B *ob)
		{
			a.push_back(ob);
		}
		
	  friend class SmartPointer;
};

class SmartPointer 
{
   FtrB oc;
   int index;
   
   public:
      SmartPointer(FtrB& objc) 
	  { 
         oc = objc;
         index = 0;
      }
   
      bool operator++() 
	  { 
         if(index >= oc.a.size()) 
			return false;
         if(oc.a[++index] == 0) 
			return false;
         return true;
      }
   
      bool operator++(int) 
      {
		return operator++();
      }
   
      // overload operator->
      B* operator->() const {
         if(!oc.a[index]) {
            cout << "Zero value";
            return (B*)0;
         }
      
         return oc.a[index];
      }
};

int main()
{
	B o[4];
	FtrB oc;	

	for(int i = 0; i < 4; i++) 
	{
			oc.add(&o[i]);
	}

	SmartPointer sp(oc);
	do 
	{
		sp->print();
	} while(sp++);

	return 0;
}




































