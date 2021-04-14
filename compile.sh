#!/bin/bash

set -e

APPDIR=/home/quyuyi/Projects/6365BuzzBlogApp/
cd $APPDIR/app/recommendation/service/server/
mkdir -p bin
g++ -o bin/recommendation_server src/recommendation_server.cpp \
    include/buzzblog/gen/buzzblog_types.cpp \
    include/buzzblog/gen/buzzblog_constants.cpp \
    include/buzzblog/gen/TAccountService.cpp \
    include/buzzblog/gen/TFollowService.cpp \
    include/buzzblog/gen/TLikeService.cpp \
    include/buzzblog/gen/TPostService.cpp \
    include/buzzblog/gen/TUniquepairService.cpp \
    include/buzzblog/gen/TRecommendationService.cpp \
    -std=c++14 -lthrift -lyaml-cpp \
    -I/$PWD/include \
    -I/usr/local/include \
    -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 \
    -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 \
    -L/usr/local/lib -lmongocxx -lbsoncxx \
    -Wl,-rpath,/usr/local/lib

bin/recommendation_server \
  --host 0.0.0.0 \
  --threads 8 \
  --port 9096 \
  --backend_filepath $APPDIR/conf/backend.yml
