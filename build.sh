#!/usr/bin/env bash
mkdir -p networkbuild;
cd networkbuild;
cmake ..;
make;
lsof -ti:4000 | xargs kill -9 > /dev/null 2>&1;
(bin/chatserver 4000 ../webchat.html;) &
echo "Hit Enter to kill server"
read enter
killall chatserver
