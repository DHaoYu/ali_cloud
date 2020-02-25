#include<iostream>
#include<string>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<cstring>
using namespace std;


class udpServer
{
public:
  udpServer(string ip_ = "127.0.0.1", int port_ = 8888)
      :sockfd(-1)
      ,ip(ip_)
      ,port(port_)
  {}

  void InitServer()
  {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        cerr << "socket error!"<<endl;
        exit(1);
    }

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t len = sizeof(local);
    if(bind(sockfd, (struct sockaddr*)&local, len) < 0)
    {
      cerr<<"bind error!"<<endl;
      exit(2);
    }

  }

  void Start()
  {
    struct sockaddr_in peer;
    for(;;)
    {
      char buf[1024];
      socklen_t len = sizeof(peer);
      ssize_t s = recvfrom(sockfd, buf, sizeof(buf)-1, \
          0, (struct sockaddr*)&peer, &len);
      if(s > 0)
      {
        buf[s] = 0;
        cout<<"client# "<<buf<<endl;
        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&peer, len);
      }
    }
  }

private:
  int sockfd;
  string ip;
  int port;
};

int main()
{
  udpServer* up = new udpServer();

  up->InitServer();
  up->Start();

  delete up;
}
