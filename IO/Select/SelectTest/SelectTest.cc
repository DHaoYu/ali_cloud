#include<iostream>
#include<sys/select.h>
#include<unistd.h>
using namespace std;

int main()
{
  fd_set rfd;
  FD_ZERO(&rfd);
  FD_SET(0, &rfd);

  for(;;)
  {
    int ret = select(1, &rfd, NULL, NULL, NULL);
    if(ret < 0)
    {
      cerr<<"select error"<<endl;
      continue;
    }
    if(FD_ISSET(0, &rfd))
    {
      char buf[1024];
      ssize_t s = read(0, buf, sizeof(buf));
      if(s < 0)
      {
        cerr<<"read error"<<endl;
        continue;
      }
      else
        cout<<buf<<endl;
    }
    else
    {
      cerr<<"fd error"<<endl;
      continue;
    }
    FD_ZERO(&rfd);
    FD_SET(0, &rfd);
  }
}
