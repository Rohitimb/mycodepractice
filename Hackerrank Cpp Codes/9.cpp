#include <sstream>
#include <vector>
#include<cstring>
#include<stdlib.h>
#include <iostream>
using namespace std;

vector<int> parseInts(string str) {
  // Complete this function
  vector<int> v;
  char *cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());

  char *p = strtok(cstr, ",");

  while (p != 0) {
    v.push_back(atoi(p));
    p = strtok(NULL, ",");
  }
  delete[] cstr;
  return v;
}

int main() {
    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for(int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }
    
    return 0;
}


