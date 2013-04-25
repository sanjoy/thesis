#!/bin/bash

DIR_NAME=`date +'%H-%M--%b-%d'`
mkdir -p $DIR_NAME
mv -f *-total $DIR_NAME
