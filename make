#!/bin/bash
mkdir -p lib
for dir in `ls -p src/ | grep /`
do
  header=`echo ${dir%/}`
  echo "#pragma once" > lib/$header
  for srcf in `find src/$dir* -type f`
  do
    echo "#include \""$srcf"\"" >> lib/$header
  done
done
