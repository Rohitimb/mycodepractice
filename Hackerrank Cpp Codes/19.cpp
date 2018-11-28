
#include <iostream>
#include<map>
#include<string>
#include<cstring>

using namespace std;

int main()
{
    int n,k,op;
    map <string,int> v;
    cin >> n;
    string str;
    
    for(int i=0;i<n;i++)
    {  
        cin >> op;
   
        if(op == 1)
        {    
            cin >> str >> k;
            
            auto itr = v.find(str);
            
            if(itr != v.end())
            {
                itr->second = itr->second + k;
            }
            else
            {
                v.insert(make_pair(str,k));
            }
        }
        else if(op == 2)
        {
            cin >> str;
            v.erase(str);
        }
        else if(op == 3)
        {
            cin >> str;
            auto itr = v.find(str);
            
            if(itr != v.end())
            {
                cout << itr->second << endl;
            }
            else
                cout << "0" << endl;
            
        }
    }
    

   
   return 0;
}


