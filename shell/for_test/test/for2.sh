#!/bin/bash 
#by authors dhy

#for i in `seq 1 15`
#do 
#  echo "The Num is $i"
#done

j=0
for ((i=1;i<=100;i++))
do
  j=`expr $i + $j`
done

echo $j

