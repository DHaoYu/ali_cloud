#!/bin/bash 
#by author dhy
#test -eq ne lt gt le ge 

Num=5
if(($Num < 10))
then
  echo "$Num is less than 10"
else
  echo "$Num is more than 10"
fi 
echo "#######################"

if [ $Num -eq 5 ]
then 
  echo "this num is eq 5"
else 
  echo "this num is not eq 5"
fi 

echo "#######################"

if [ $Num -ne 5 ]
then 
  echo "the num is not eq 5"
else 
  echo "the num is not not eq 5"
fi 
echo "#######################"
if [ $Num -gt 4 ]
then
  echo "the num is gt 4"
else 
  echo "the num is not ge 4"
fi
echo "#######################"
