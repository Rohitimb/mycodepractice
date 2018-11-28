#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;


int main() {
    int n,b,a;
    set <int> s;
    cin >> n;

    for(int i=0;i<n;i++)
    {
        cin >> a >> b;
        switch(a)
        {
            case 1:
              s.insert(b);
              break;
            
            case 2:
                s.erase(b);
                break;

            case 3:
              //set<int>::iterator itr2 = s.find(b);
                auto itr = s.find(b);
                if(itr != s.end())
                    cout << "Yes"<<endl;
                else
                    cout << "No" << endl;
              break;
        };
    }
    return 0;
}




