#include"threadPool.hpp"


class tcpServer
{
public:
  tcpServer(int port_ = 8888)
    :lis_sock(-1)
    ,port(port_)
    ,tp(new ThreadPool())
  {}

  void InitServer()
  {
    lis_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(lis_sock < 0)
    {
      cerr<<"socket error"<<endl;
      exit(1);
    }

    int opt = 1;
    setsockopt(lis_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(lis_sock, (struct sockaddr*)&local, sizeof(local)) < 0)
    {
      cerr<<"bind error!"<<endl;
      exit(2);
    }

    if(listen(lis_sock, 5) < 0)
    {
      cerr<<"listen error!"<<endl;
      exit(3);
    }
    //初始化套接字步骤已完成
    
    tp->InitThreadPool();
  }

  void Start()
  {
    for(;;)
    {
      struct sockaddr_in peer;
      socklen_t len = sizeof(peer);
      int sock = accept(lis_sock, (struct sockaddr*)&peer, &len);
      if(sock < 0)
      {
        cerr<<"accept error!"<<endl;
        continue;
      }
      cout<<"get a client link ..."<<endl;
      Task t(sock);
      tp->PushTask(t);
    }
  }
  ~tcpServer()
  {
    if(tp->IsEmpty())
      delete tp;
    if(lis_sock > 0)
      close(lis_sock); //节省sock资源
  }
private:
  int lis_sock;
  int port;
  ThreadPool* tp;
};


int main()
{
  tcpServer* tsp = new tcpServer();
  tsp->InitServer();
  tsp->Start();

  delete tsp;
  return 0;
}
