#pragma once
#include<sys/select.h>
#include<vector>
#include<cstdlib>
#include<algorithm>
//负责：描述符数组和rfd相关事件
class Select
{
  public:
    Select()
    :fd_arr(sizeof(fd_set)*8-1, -1)
    {
      FD_ZERO(&rfd); 
    }

    void FdSet()
    {
      for(size_t i = 0; i < fd_arr.size(); i++)
      {
        if(fd_arr[i] == -1)
          continue;
        FD_SET(fd_arr[i], &rfd);
      }
    }

    bool IsFdSet(int fd)
    {
      return FD_ISSET(fd, &rfd);
    }

    void ModifiArr(int pos, int val)
    {
      fd_arr[pos] = val;
    }

    int GetMostArr()
    {
      return *std::max_element(fd_arr.begin(), fd_arr.end());
    }
    
    int GetArrVal(int pos)
    {
      return fd_arr[pos];
    }

    fd_set GetFdSet()
    {
      return rfd;
    }
    
    bool PushSock(int fd)
    {
      for(size_t i = 0; i < fd_arr.size(); i++)
      {
        if(fd_arr[i] == -1)
        {
          fd_arr[i] = fd;
          return true;
        }
      }
      return false;
    }
  private:
    void InitFD()
    {
      for(size_t i = 0; i < fd_arr.size(); i++)
      {
        FD_SET(fd_arr[i], &rfd);
      }
    }

  private:
    fd_set rfd;
    std::vector<int> fd_arr;
};
