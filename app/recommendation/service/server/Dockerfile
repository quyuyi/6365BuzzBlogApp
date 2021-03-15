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

# Install software dependencies.
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

# Add Mongodb repository.
RUN wget -qO - https://www.mongodb.org/static/pgp/server-4.4.asc | sudo apt-key add - \
  && echo "deb [ arch=amd64,arm64 ] https://repo.mongodb.org/apt/ubuntu focal/mongodb-org/4.4 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-4.4.list \
  && apt-get update

# Install mongodb.
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y \
  mongodb-org

# Install Thrift 0.13.
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y \
  libthrift-0.13.0=0.13.0-2build2 \
  libthrift-dev=0.13.0-2build2

# Install libpqxx 6.4.5.
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y \
  libpqxx-6.4=6.4.5-2build1 \
  libpqxx-dev=6.4.5-2build1

# Install libyaml 0.6.2.
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y \
  libyaml-cpp0.6=0.6.2-4ubuntu1 \
  libyaml-cpp-dev=0.6.2-4ubuntu1
    
# Copy cxxopts 2.2.1.
RUN cd /tmp \
  && wget https://github.com/jarro2783/cxxopts/archive/v2.2.1.zip \
  && unzip v2.2.1.zip \
  && cp cxxopts-2.2.1/include/cxxopts.hpp /usr/local/include

# Copy service client libraries.
COPY include include

# Copy source code.
COPY src src

# TODO: change compile: delete -lpqxx -lpq; add mongodb related compilation flag
# Compile source code.
RUN mkdir bin && g++ -o bin/recommendation_server src/recommendation_server.cpp \
    include/buzzblog/gen/buzzblog_types.cpp \
    include/buzzblog/gen/buzzblog_constants.cpp \
    include/buzzblog/gen/TAccountService.cpp \
    include/buzzblog/gen/TFollowService.cpp \
    include/buzzblog/gen/TLikeService.cpp \
    include/buzzblog/gen/TPostService.cpp \
    include/buzzblog/gen/TUniquepairService.cpp \
    include/buzzblog/gen/TRecommendationService.cpp \
    -std=c++14 -lthrift -lpqxx -lpq -lyaml-cpp \
    -I/opt/BuzzBlogApp/app/recommendation/service/server/include \
    -I/usr/local/include

# TODO: change from postgres to mongodb
# Start the server.
CMD ["/bin/bash", "-c", "bin/recommendation_server --host 0.0.0.0 --threads $threads --port $port --backend_filepath $backend_filepath --postgres_user $postgres_user --postgres_password $postgres_password --postgres_dbname $postgres_dbname"]
