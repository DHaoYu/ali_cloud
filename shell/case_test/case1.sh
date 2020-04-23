#!/bin/bash 
#author by dhy
#test case 

echo "Please enter from 1 to 4:"
read num
case $num in 
  1) echo "you select 1"
    ;;
  2) echo "you select 2"
    ;;
  3) echo "you select 3"
    ;;
  4) echo "you select 4"
    ;;
  *) echo "you not select 1~4"
    ;;
esac
