#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int main() {
  string str1, str2;
  char t;
  
  cin >> str1;
  cin  >> str2;

  cout << str1.length() << " " << str2.length() << endl;
  cout << str1 + str2 << endl;

  char *p = new char[str1.length() + 1];
  char *q = new char[str2.length() + 1];

  strcpy(p, str1.c_str());
  strcpy(q, str2.c_str());

  t = *p;
  *p = *q;
  *q = t;

  str1 = string(p);
  str2 = string(q);

  cout << str1 << " " << str2 << endl;
  return 0;
}

