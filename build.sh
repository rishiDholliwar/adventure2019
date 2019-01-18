mkdir -p networkbuild;
cd networkbuild;
cmake ..;
make;
lsof -ti:4000 | xargs kill -9 >> /dev/null;
bin/chatserver 4000 ../webchat.html;


