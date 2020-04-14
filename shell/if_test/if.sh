#!/bin/bash 
#author by dhy
#test if 

VAR=123

if ((VAR == "123"))
then
  echo "VAR is eq 123"
else
  echo "VAR is not eq 123"
fi

var=100

if [ $var -eq "100" ]
then 
  echo "var is eq 100"
else 
  echo "var is mot eq 100"
fi
