#!/bin/sh

if [[ $# -gt 1 || $# -eq 1 &&  $1 != "-make" ]]; then
  echo "Usage:"
  echo "$0 [-make]"
  exit 1;
fi

TECHNOLOGIES=(cpp cuda)

for TECH in ${TECHNOLOGIES[@]}; do
  CWD=`pwd`
  DIRECTORY="${TECH}_build"
  mkdir $DIRECTORY 
  cd $DIRECTORY
  cmake -DTECHNOLOGY:STRING=${TECH} ../src
  if [[ $# -eq 1 ]]; then # -make was specified
    make
  fi
  cd $CWD
done
