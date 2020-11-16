#!/bin/bash

for dir in `ls -p src/ | grep /`
do
  header=`echo ${dir%/}`
  echo "#pragma once" > $header
  for srcf in `find src/$dir* -type f`
  do
  echo "#include \""$srcf"\"" >> $header
  done
done
