#!/bin/bash 
#author by dhy
#test ! -o -a

a=10
b=20

if [ !false ]
then
  echo "use \"!false\" to true branch"
fi

if [ $a -lt 20 -o $b -lt 10 ]
then 
  echo "a < 20 or b < 10"
fi 

if [ $a -lt 100 -a $a -lt $b ]
then 
  echo "a < 100 and a < b"
fi
