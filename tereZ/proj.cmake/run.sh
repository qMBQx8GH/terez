#!/usr/bin/env sh

# Absolute path to this script. /home/user/bin/foo.sh
SCRIPT=$(readlink -f $0)
# Absolute path this script is in. /home/user/bin
SCRIPTPATH=`dirname $SCRIPT`
cd $SCRIPTPATH

mkdir build
cd build

#generate cmake project in the "build" folder
cmake ..

#build it
make

#move to working data folder with resources
cd ../../data

#run executable
./../proj.cmake/build/tereZ
