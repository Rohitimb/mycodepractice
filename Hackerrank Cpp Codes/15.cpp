#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> v;
  int n, i, k;
  cin >> n;
  for (i = 0; i < n; i++) {
    cin >> k;
    v.push_back(k);
  }

  sort(v.begin(), v.end());
  for (auto i = v.begin(); i != v.end(); i++)
    cout << *i << " ";
    cout << "\n";
  return 0;
}

