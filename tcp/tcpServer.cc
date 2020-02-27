#include<iostream>
#include<string>
#include<cstring>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;

class tcpServer
{
public:
  tcpServer(int port_ = 8888)
    :sockfd(-1), port(port_)
  {}

  void InitServer()
  {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
      cerr<<"socket error!"<<endl;
      exit(1);
    }

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = htonl(INADDR_ANY);
   // socklen_t len = sizeof(local);
    if(bind(sockfd, (struct sockaddr*)&local, sizeof(local)) < 0)
    {
      cerr<<"bind error!"<<endl;
      exit(2);
    }

    if(listen(sockfd, 5) < 0)
    {
      cerr<<"listen error!"<<endl;
      exit(3);
    }

  }

  void Start()
  {
    int sock = -1;
    struct sockaddr_in peer;
    socklen_t len = sizeof(peer);
    sock = accept(sockfd, (struct sockaddr*)&peer, &len);
    if(sock < 0)
    {
      cerr<<"accept error!"<<endl;
      exit(4);
    }
    //处理客户端消息
    ServiceIO(sock);
  }

private:
  void ServiceIO(int sock)
  {
    for(;;)
    {
      char buf[1024];
      ssize_t s = read(sock, (void*)buf, sizeof(buf)-1);
      if(s > 0)
      {
        buf[s] = 0;
        cout<<"client say# "<<buf<<endl;
      }
      else if(s == 0)
      {
        cout<<"client exit"<<endl;
      }
      else
      {
        continue;
      }
      
      buf[s] = ' ';
      string msg(buf, strlen(buf));
      msg += "server recived!";
      send(sock, msg.c_str(), msg.size(), 0);
      msg.clear();
    }
  }


private:
  int port;
  int sockfd;
};

int main()
{
  tcpServer* tsp = new tcpServer();
  tsp->InitServer();
  tsp->Start();

  delete tsp;
}
