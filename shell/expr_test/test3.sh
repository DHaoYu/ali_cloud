#!/bin/bash 
#author by dhy
#test && ||

a=10
b=20

if (($a<100 && $b<100))
then
  echo "use && success"
else
  echo "false"
fi

if (($a>15 || $b>15))
then 
  echo "use || success"
else 
  echo "false"
fi
