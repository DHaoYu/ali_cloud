#include<iostream>
#include<signal.h>
using namespace std;

int flag = 0;

void handler(int sig)
{
  cout<<"change flag from 0 to 1"<<endl;
  flag = 1;
}

int main()
{
  signal(2, handler);
  while(!flag)
    ;
  cout<<"process quit normal"<<endl;
}
