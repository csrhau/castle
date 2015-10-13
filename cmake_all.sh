#!/bin/sh

if [[ $# -gt 1 || $# -eq 1 && $1 != "-make" ]]; then
  echo "Usage:"
  echo "$0 [-make]"
  exit 1;
fi

CASTLE_TECHNOLOGIES=(cpp cuda)

for TECH in ${CASTLE_TECHNOLOGIES[@]}; do
  CWD=`pwd`
  DIRECTORY="${TECH}_build"
  mkdir $DIRECTORY 
  cd $DIRECTORY
  cmake -DCASTLE_TECHNOLOGY:STRING=${TECH} ../src
  if [[ $# -eq 1 ]]; then # -make was specified
    make -j
  fi
  cd $CWD
done
