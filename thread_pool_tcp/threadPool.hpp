#pragma once
#include<iostream>
#include<string>
#include<map>
#include<queue>
#include<pthread.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>

using namespace std;

std::map<string, string> dict{
   {"apple", "苹果"},
   {"banana", "香蕉"},
   {"orange", "橘子"},
};

class Task
{
public:
  Task(int fd_)
    :fd(fd_)
  {}

  void Run()
  {
    while(true)
    {
      char buf[1024];
      ssize_t s = recv(fd, buf, sizeof(buf)-1, 0);
      if(s > 0)
      {
        buf[s-2] = 0;
        cout<<"client say# "<< buf <<endl;
      }
      else if(s == 0)
      {
        cout<<"client exit!"<<endl;
        break;
      }
      else
      {
        cout<<"s < 0"<<endl;
        break;
      }
    
      string str;
      auto it = dict.find(buf);
      if(it == dict.end())
        str = "unknow";
      else
        str = it->second;
      send(fd, str.c_str(), str.size(), 0);
    }
    close(fd);
  }

  ~Task()
  {}

private:
  int fd;
};


class ThreadPool
{
public:
  ThreadPool(int num_ = 5)
    :num(num_)
  {
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
  }

  ~ThreadPool()
  {
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
  }

  void PushTask(Task t)
  {
    LockQueue();
    q.push(t);
    UnLockQueue();
    ThreadSignal();
  }

  Task PopTask()
  {
    Task t = q.front();
    //LockQueue();  //可不能在这加锁
    q.pop();
   // UnLockQueue();
    return t; 
  }
  
  static void* Routine(void* args)
  {
    ThreadPool* self = (ThreadPool*)args;
    pthread_detach(pthread_self());
    for(;;)
    {
      self->LockQueue();
      while(self->IsEmpty())
      {
        self->ThreadWait();
      }
      Task t = self->PopTask();
      self->UnLockQueue();
      t.Run();
    }
  }

  void InitThreadPool()
  {
    pthread_t tid;
    for(int i = 0; i < num; i++)
    {
      pthread_create(&tid, NULL, Routine, (void*)this);
    }
  }

  bool IsEmpty()
  {
    return q.empty();
  }

private:
  void LockQueue()
  {
    pthread_mutex_lock(&lock);
  }

  void UnLockQueue()
  {
    pthread_mutex_unlock(&lock);
  }

  void ThreadSignal()
  {
    pthread_cond_signal(&cond);
  }

  void ThreadWait()
  {
    pthread_cond_wait(&cond, &lock);
  }

private:
  queue<Task> q;
  int num;
  pthread_mutex_t lock;
  pthread_cond_t cond;
};
