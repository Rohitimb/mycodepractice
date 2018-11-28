#include<iostream>

using namespace std;

int main()
{

    int *a,n;
    cin >> n;
    a = new int[n];
    for(int i=0;i<n;i++)
    cin >> a[i];

    for(int j=n-1;j>0;j--)
    cout << a[j] << " ";

    cout << a[0] << endl;
    return 0;
}
