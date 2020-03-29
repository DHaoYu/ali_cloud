#!/bin/bash 
#by authors dhy

for i in `find . -name "*.sh"`
do 
  tar -czvf 2020all.tgz $i
done
