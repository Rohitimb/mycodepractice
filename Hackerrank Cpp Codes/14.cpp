#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Person
{
    public:
        string name;
        int age;
        virtual void getdata(){}
        virtual void putdata(){}
};

class Professor : public Person
{
  int publications,cur_id;
public:
static int c;
 Professor()
 {
     c++;
     cur_id = c;
 }
 void putdata() {
  cout << name << " " << age << " " << publications << " " << cur_id << endl;
  }
  void getdata()
  {
      cin >> name;
      cin >> age;
      cin >> publications;
  }
};

int Professor ::c = 0;


class Student : public Person
{
  static int c;

  int marks[6], cur_id;
public:
  Student() 
  {
       c++;
       cur_id = c;
  }

  void putdata()
  {
        int t = 0;
        for(int i=0;i<6;i++)
        {
            t+=marks[i];
        }
        cout << name << " " << age << " " << t << " " << cur_id << endl;
  }
  void getdata()
  {
      cin >> name;
      cin >> age;
      for(int i =0;i < 6;i++)
      {
          cin >> marks[i];
      }
  }
};

int Student ::c = 0;

int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}

