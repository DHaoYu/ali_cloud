#!/bin/bash 
#test unitl

i=0

until [ ! $i -lt 10 ]
do 
  echo "$i"
  ((i++))
done
