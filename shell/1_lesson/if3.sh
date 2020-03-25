#!/bin/bash
#auto if 
#by authors dhy


scores=$1
if [ -z $scores ]; then 
  echo "Usage:$0 add scors"
  exit
fi 

if [[ $scores -gt 85 ]]; then
  echo "very good $scores"
elif [[ $scores -gt 75 ]]; then 
  echo "good $scores"
elif [[ $scores -gt 60 ]]; then 
  echo "pass $scores"
else
  echo "no pass $scores"
fi
