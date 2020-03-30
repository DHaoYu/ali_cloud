#!/bin/bash 
#by authors dhy
#test case select 

PS3="Please select you Menu:"

select i in "CentOS" "RedHat" "Ubuntu"
do 
  case $i in 
    CentOS)
      echo "you select 1 centos";;
    RedHat)
      echo "you select 2 redhat";;
    Ubuntu)
      echo "you select 3 ubuntu";;
    *)
      echo "Usage is $0 {1|2|3}"
  esac
done
