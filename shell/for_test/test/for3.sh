#!/bin/bash 
#author by dhy
#backup tar all .sh file

for i in find ./ -name "*.sh"
do 
  tar -czf backup_sh.tgz $i
done
