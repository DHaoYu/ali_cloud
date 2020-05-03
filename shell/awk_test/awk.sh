#!/bin/bash 
#author by dhy

Num=$1

#echo $Num
#awk '{print $'$Num'}'
awk -F, '{print $'$Num'}'
