#!/usr/bin/env bash
PORT=4000
JOBS=0
for var in "$@"
do
	IFS='=' read -r -a array <<< "$var"
	declare "${array[0]}"="${array[1]}"
done
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
mkdir -p $DIR/networkbuild;
cd $DIR/networkbuild;
cmake ..;
if [ -z $JOBS ]
then
	make;
else
	make -j$JOBS;
fi
lsof -ti:$PORT | xargs kill -9 > /dev/null 2>&1;
(bin/chatserver $PORT ../webchat.html;) &
echo "Running server on port: $PORT"
echo "Hit Enter to kill server"
read enter
killall chatserver
