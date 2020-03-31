#!/bin/bash 
#by authors dhy
#test until 

a=10
until [[ $a -lt 0 ]];do 
  echo "The number is a = $a"
  ((a--))
done
