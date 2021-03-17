#!/bin/bash

# install mongo c driver
# ref: http://mongoc.org/libmongoc/current/installing.html
wget https://github.com/mongodb/mongo-c-driver/releases/download/1.17.4/mongo-c-driver-1.17.4.tar.gz
tar xzf mongo-c-driver-1.17.4.tar.gz
sudo apt-get install cmake libssl-dev libsasl2-dev
mkdir cmake-build
cd cmake-build

cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF -DCMAKE_BUILD_TYPE=Release -DBSONCXX_POLY_USE_MNMLSTC=1 ..

cmake --build .
sudo cmake --build . --target install


# install mongo cxx driver
# ref: http://mongocxx.org/mongocxx-v3/installation/linux/
curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.6.2/mongo-cxx-driver-r3.6.2.tar.gz
tar -xzf mongo-cxx-driver-r3.6.2.tar.gz
cd mongo-cxx-driver-r3.6.2/build

cmake ..                                \
    -DBSONCXX_POLY_USE_BOOST=1          \
    -DCMAKE_BUILD_TYPE=Release          \
    -DCMAKE_INSTALL_PREFIX=/usr/local

cmake --build .
sudo cmake --build . --target install

