#!/bin/bush
#auto if test
#by authors dhy

DIR=/home/donghaoyu/test

if [ ! -d /home/donghaoyu/test ];then
  mkdir -p $DIR
  echo "This dir is create success!"  
else
  echo "This dir is exist, exit!"
fi
