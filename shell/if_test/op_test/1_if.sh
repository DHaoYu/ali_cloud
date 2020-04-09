#!/bin/bash 
#by author dhy
#test -f -d

#DIR="/home/donghaoyu/code/shell/if_test/op_test/test.sh"
DIR="./test"


if [ ! -d $DIR ]
then
  echo "this dir is not exist!"
  mkdir $DIR 
else
  echo "this dir is exist! exit"
fi
