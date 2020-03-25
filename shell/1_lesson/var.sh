#!/bin/bash
#define path var
#author by dhy

a=123

echo "UID is $UID"
echo "PWD is $PWD"
echo "This is my first shell var a = $a"
echo "0 is $0"  #0 1 2 为命令行参数
echo "1 is $1, 2 is $2"

echo $? #退出码
echo "The \$? is $?"
echo "The \$* is $*"
echo "The \$# is $#"
