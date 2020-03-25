#!/bin/bash
#auto test files >> and cat
#by authors dhy

File=/home/donghaoyu/code/shell/1_lesson/test.txt

if [ ! -f $File ];then
  echo "OK" >> $File 
else
  cat $File
fi
