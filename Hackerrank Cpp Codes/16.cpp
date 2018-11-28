#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int n,k;
    cin >> n;
    vector <int> v;
    for(int i=0;i<n;i++)
    {
        cin >> k;
        v.push_back(k);
    }
    cin >> k;
    v.erase(v.begin() + k-1);

    cin >> n >> k;
    
    v.erase(v.begin() + n-1, v.begin() + k-1);

    cout << v.size() << endl;
    for(auto i=v.begin();i!=v.end();i++)
    cout << *i << " ";

    cout << endl;

    return 0;
}

