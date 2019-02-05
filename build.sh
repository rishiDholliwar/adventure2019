#!/usr/bin/env bash
PORT=4000
JOBS="0"
SERVER=TRUE
CLEAN=FALSE
for var in "$@"
do
	if [ "$var" == "--help" ] || [ "$var" == "-h" ]
	then
		echo "Usage:"
		echo "./build.sh [PORT=####] [JOBS=#] [SERVER=FALSE] [CLEAN=TRUE]"
		echo "PORT 	 - Set the server port"
		echo "         DEFAULT: 4000"
		echo "JOBS 	 - Builds faster, sets the number of cores to use when building"
		echo "         DEFAULT: 0"
		echo "SERVER - Set it to FALSE to not run server at the end"
		echo "         DEFAULT: TRUE"
		echo "CLEAN  - Removes previous networkbuild directory before building"
		echo "         DEFAULT: FALSE"
		echo "Example: ./build.sh PORT=9999 JOBS=4"
		exit 0
	fi
	IFS='=' read -r -a array <<< "$var"
	declare "${array[0]}"="${array[1]}"
done
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
if [ "$CLEAN" == "TRUE" ]
then
	echo "Removing artifacts..."
	rm -rf $DIR/networkbuild
fi
mkdir -p $DIR/networkbuild;
cd $DIR/networkbuild;

BOOST=""
if [ -d "/usr/shared/CMPT/faculty/wsumner/base/" ]
then
	BOOST='-DBOOST_ROOT=/usr/shared/CMPT/faculty/wsumner/base/ '
fi
cmake ${BOOST}..;
if [ $? -ne 0 ]
then
	echo "Failed: cmake"
	exit -1
fi
if [ "$JOBS" == "0" ]
then
	make;
else
	make -j$JOBS;
fi
if [ $? -ne 0 ]
then
	echo "Failed: make"
	exit -1
fi
if [ "$SERVER" == "FALSE" ]
then
	exit 0
fi
lsof -ti:$PORT | xargs kill -9 > /dev/null 2>&1;
(bin/chatserver $PORT ../webchat.html;) &
echo "Running server on port: $PORT"
echo "Hit Enter to kill server"
read enter
killall chatserver
