# Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
# Systems

# Define base configuration.
FROM ubuntu:20.04
WORKDIR /opt/BuzzBlogApp/app/recommendation/service/server

# Declare environment variables.
ENV threads null
ENV port null
ENV backend_filepath null
ENV postgres_user null
ENV postgres_password null
ENV postgres_dbname null

# # Install software dependencies.
RUN apt-get update \
  && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    apt-utils \
    automake \
    bison \
    flex \
    g++ \
    git \
    gnupg2 \
    libboost-all-dev \
    libevent-dev \
    libssl-dev \
    libtool \
    lsb-core \
    make \
    pkg-config \
    wget \
    unzip

# # Add Mongodb repository.
# RUN wget -qO - https://www.mongodb.org/static/pgp/server-4.4.asc | apt-key add - \
#   && echo "deb [ arch=amd64,arm64 ] https://repo.mongodb.org/apt/ubuntu focal/mongodb-org/4.4 multiverse" | tee /etc/apt/sources.list.d/mongodb-org-4.4.list \
#   && apt-get update

# # Install mongodb.
# RUN DEBIAN_FRONTEND=noninteractive apt-get install -y \
#   mongodb-org

# # install mongo c driver
# # ref: http://mongoc.org/libmongoc/current/installing.html
# RUN cd /tmp \
#   && wget https://github.com/mongodb/mongo-c-driver/releases/download/1.17.4/mongo-c-driver-1.17.4.tar.gz \
#   && tar xzf mongo-c-driver-1.17.4.tar.gz \
#   && apt-get install cmake libssl-dev libsasl2-dev \
#   && cd mongo-c-driver-1.17.4 \
#   && mkdir cmake-build \
#   && cd cmake-build \
#   && cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF -DCMAKE_BUILD_TYPE=Release .. \
#   && cmake --build . \
#   && cmake --build . --target install \
#   && rm -rf /tmp/*

# # install mongo cxx driver
# # ref: http://mongocxx.org/mongocxx-v3/installation/linux/
# RUN cd /tmp \
#   && curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.6.2/mongo-cxx-driver-r3.6.2.tar.gz \
#   && tar -xzf mongo-cxx-driver-r3.6.2.tar.gz \
#   && cd mongo-cxx-driver-r3.6.2/build \
#   && cmake ..                             \
#       -DBSONCXX_POLY_USE_BOOST=1          \
#       -DCMAKE_BUILD_TYPE=Release          \
#       -DCMAKE_INSTALL_PREFIX=/usr/local   \
#   && cmake --build . \
#   && cmake --build . --target install \
#   && rm -rf /tmp/*

# Install Thrift 0.13.
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y \
  libthrift-0.13.0=0.13.0-2build2 \
  libthrift-dev=0.13.0-2build2

# Install libyaml 0.6.2.
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y \
  libyaml-cpp0.6=0.6.2-4ubuntu1 \
  libyaml-cpp-dev=0.6.2-4ubuntu1
    
# Copy cxxopts 2.2.1.
RUN cd /tmp \
  && wget https://github.com/jarro2783/cxxopts/archive/v2.2.1.zip \
  && unzip v2.2.1.zip \
  && cp cxxopts-2.2.1/include/cxxopts.hpp /usr/local/include \
  && rm -rf /tmp/*

# Copy service client libraries.
COPY include include

# Copy source code.
COPY src src

# # Compile source code.
# RUN mkdir bin && g++ -o bin/recommendation_server src/recommendation_server.cpp \
#     include/buzzblog/gen/buzzblog_types.cpp \
#     include/buzzblog/gen/buzzblog_constants.cpp \
#     include/buzzblog/gen/TAccountService.cpp \
#     include/buzzblog/gen/TFollowService.cpp \
#     include/buzzblog/gen/TLikeService.cpp \
#     include/buzzblog/gen/TPostService.cpp \
#     include/buzzblog/gen/TUniquepairService.cpp \
#     include/buzzblog/gen/TRecommendationService.cpp \
#     -std=c++14 -lthrift -lyaml-cpp \
#     -I/opt/BuzzBlogApp/app/recommendation/service/server/include \
#     -I/usr/local/include \
#     -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 \
#     -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 \
#     -L/usr/local/lib -lmongocxx -lbsoncxx \
#     -Wl,-rpath,/usr/local/lib 

COPY bin bin

# Start the server.
CMD ["/bin/bash", "-c", "bin/recommendation_server --host 0.0.0.0 --threads $threads --port $port --backend_filepath $backend_filepath --postgres_user $postgres_user --postgres_password $postgres_password --postgres_dbname $postgres_dbname"]
