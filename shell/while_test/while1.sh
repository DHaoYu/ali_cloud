#!/bin/bash 
#by authors dhy

i=0
#while [[ $i -lt 10 ]]

while (($i < 10))
do 
  echo "The number is $i"
  ((i++))
done
