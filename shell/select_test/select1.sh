#!/bin/bash 
#by authors dhy

function nginx_install()
{
  echo "Install nginx..."
}

function mysql_install()
{
  echo "Install mysql..."
}

function php_install()
{
  echo "Install PHP..."
}

PS3="Please select install Menu:"
select i in "Nginx" "Mysql" "PHP"
do

case $i in 
  Nginx )
    nginx_install;;
  Mysql )
    mysql_install;;
  PHP )
    php_install;;
  * )
    echo "usage: $0 {Nginx | Mysql | PHP}";;
esac

done


