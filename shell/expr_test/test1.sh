#!/bin/bash 
#author by dhy
#test expr for + - * / 

a=2
b=4

#echo "a + b: `expr $a + $b`"
#echo "a - b: `expr $a - $b`"
#echo "a * b: `expr $a \* $b`"
#echo "a / b: `expr $a / $b`"
#echo "a % b: `expr $a % $b`"

if [ $a == $b ]
then
  echo "a == b"
else
  a=$b
  echo "a assign b"
  if [ $a != $b ]
  then 
    echo "a != b"
  else 
    echo "a == b"
  fi 
fi
