#pragma once 
#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/select.h>
#include<unistd.h>
#include"SelectServer.hpp"

using namespace std;


class Server
{
  public:
    Server()
      :sel()
      ,lis_sock(-1)
  {}

    void InitServer()
    {
      lis_sock = socket(AF_INET, SOCK_STREAM, 0);
      if(lis_sock < 0)
      {
        cerr<<"socket error!"<<endl;
        exit(2);
      }

      struct sockaddr_in local;
      local.sin_family = AF_INET;
      local.sin_port = htons(8888);
      local.sin_addr.s_addr = htonl(INADDR_ANY);
      if((bind(lis_sock, (struct sockaddr*)&local, sizeof(local))<0))
      {
           cerr<<"bind error!"<<endl;
           exit(3);
      }

      if(listen(lis_sock, 1000) < 0)
      {
        cerr<<"listen error!"<<endl;
        exit(4);
      }
    }

    void Run()
    {
      for(;;)
      {
        sel.ModifiArr(0, lis_sock);
        sel.FdSet();
        fd_set rfds = sel.GetFdSet();
        struct timeval timeout = {3, 0};
        int n = select(sel.GetMostArr()+1, &rfds, NULL, NULL, &timeout);
        if(n < 0)
        {
          cerr<<"select error!"<<endl;
          sleep(1);
          continue;
        }
        else if(n == 0)
        {
          cout<<"timeout..."<<endl;
          continue;
        }
        else
        {
          for(size_t i = 0; i < sizeof(rfds)*8; i++)
          {
            //cout<<i<<":"<<sel.GetArrVal(i)<<endl;
            //sleep(1);
            if(sel.IsFdSet(sel.GetArrVal(i)))
            {
              cout<<"fd lis_sock:"<<lis_sock<<endl;
              int sock = sel.GetArrVal(i);
              cout<<"fd sock:"<<sock<<"  i:"<<i<<endl;
              if(sock == lis_sock)
              {
                cout<<"new link"<<endl;
                //新连接
                //cout<<"sock:"<<sock<<" lis_sock:"<<lis_sock<<endl;
                HandleLink();
              }
              else 
              {
                //IO操作
                cout<<"IO...."<<endl;
                char buf[10240];
                ssize_t s = recv(sock, buf, sizeof(buf)-1, 0);
                if(s > 0)
                  HandleIO(sock);
                else if(s == 0)
                  cout<<"cilent quit"<<endl;
                else
                {
                  cerr<<"recv error"<<endl;
                  sleep(1);
                  continue;
                } 
                //close(sel.GetArrVal(i));
                //sel.ModifiArr(i, -1);
              }
            }
          }
        }
      }
    }

    void HandleLink()
    {
      struct sockaddr_in peer;
      socklen_t len = sizeof(peer);
      int sock = accept(lis_sock, (struct sockaddr*)&peer, &len);
      cout<<"accept sock"<<sock<<endl;
      if(sock < 0)
      {
        cerr<<"accept error!"<<endl;
        return;
      }
      if(!sel.PushSock(sock))
        close(sock);
      cout<<"get a new link..."<<endl;
    }

    void HandleIO(int sock)
    {
      cout<<"HandleIO"<<endl;
      string response = "HTTP/1.0 200 OK\r\n\r\n<html><h1>Hello world</h1></html>";
      send(sock, response.c_str(), response.size(), 0);
    }

  private:
    Select sel;
    int lis_sock;
};

