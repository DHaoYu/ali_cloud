#!/bin/bash 
#author by dhy
#test array usage

arr=(123 A Abc 'D' "EFG")

for((i=0; i<5;i++))
do 
  echo "the $i is : ${arr[$i]}"
  #if [ $i -eq "1" ]
  if (($i > '1'))
  then
    echo "the second element is: ${arr[$i]}"
  fi
done
