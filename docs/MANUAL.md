# User Manual
This running example shows how to deploy BuzzBlog in your local machine with
a simple topology:
* Load Balancer: 1 NGINX server
* API Gateway: 2 uWSGI servers
* Account service: 2 Thrift multithreaded servers
* Account database: 1 PostgreSQL database server
* Follow service: 1 Thrift multithreaded server
* Like service: 1 Thrift multithreaded server
* Post service: 1 Thrift multithreaded server
* Post database: 1 PostgreSQL database server
* Uniquepair service: 1 Thrift multithreaded server
* Uniquepair database: 1 PostgreSQL database server

After running this example, adapting configuration files and commands to deploy
BuzzBlog with a more complex topology in the cloud should be trivial.

## Configuration
### `conf/backend.yml`
In `conf/backend.yml`, set the hostnames and ports of services and databases.
The API Gateway and backend services read this file at their initialization to
discover which servers they should connect to.
```
account:
  service:
    - "172.17.0.1:9090"
    - "172.17.0.1:9091"
  database: "172.17.0.1:5433"
follow:
  service:
    - "172.17.0.1:9092"
like:
  service:
    - "172.17.0.1:9093"
post:
  service:
    - "172.17.0.1:9094"
  database: "172.17.0.1:5434"
uniquepair:
  service:
    - "172.17.0.1:9095"
  database: "172.17.0.1:5435"
```

### `conf/nginx.conf`
In `conf/nginx.conf`, configure the NGINX server used as a load balancer. Here
we set the server to listen on port 80, use 8 worker processes, and limit the
number of simultaneous connections that can be opened by a worker process to
512. Also, define the hostnames and ports of the API Gateway servers to which
client requests are forwarded (here we use `172.17.0.1:8080` and
`172.17.0.1:8081`).
```
worker_processes 8;

events {
  worker_connections 512;
}

http {
  include /etc/nginx/mime.types;
  default_type application/octet-stream;
  keepalive_timeout 0;
  upstream backend {
    server 172.17.0.1:8080;
    server 172.17.0.1:8081;
  }
  server {
    listen 80;
    location / {
      proxy_pass http://backend;
    }
  }
}
```

### `conf/uwsgi.ini`
In `conf/uwsgi.ini`, configure the uWSGI server on which the Python application
that implements the API Gateway runs. Here we only set the server to listen on
port 81. To learn more about the uWSGI configuration parameters, check the
[documentation](https://uwsgi-docs.readthedocs.io/en/latest/Configuration.html).
```
[uwsgi]
http-socket = 0.0.0.0:81
```

## Deployment
### Load Balancer
1. Run a Docker container based on the official NGINX image. Here we name the
container `loadbalancer`, publish its port 80 to the host port 8888, and
bind-mount the `conf/nginx.conf` configuration file.
```
sudo docker run \
    --name loadbalancer \
    --publish 8888:80 \
    --volume $(pwd)/conf/nginx.conf:/etc/nginx/nginx.conf \
    --detach \
    nginx:1.18.0
```

### API Gateway
1. Generate Thrift code and copy client libraries.
```
./utils/generate_and_copy_code.sh
```
2. Build the Docker image. Here we name the image `apigateway:latest`.
```
cd app/apigateway/server
sudo docker build -t apigateway:latest .
```
3. Run two Docker containers based on the newly built image. Here we name these
containers `apigateway1` and `apigateway2`, publish their port 81 to the host
ports 8080 and 8081, respectively, and bind-mount `conf/backend.yml` and
`conf/uwsgi.ini` configuration files in both.
```
cd ../../..
sudo docker run \
    --name apigateway1 \
    --publish 8080:81 \
    --volume $(pwd)/conf/backend.yml:/etc/opt/BuzzBlogApp/backend.yml \
    --volume $(pwd)/conf/uwsgi.ini:/etc/uwsgi/uwsgi.ini \
    --detach \
    apigateway:latest
sudo docker run \
    --name apigateway2 \
    --publish 8081:81 \
    --volume $(pwd)/conf/backend.yml:/etc/opt/BuzzBlogApp/backend.yml \
    --volume $(pwd)/conf/uwsgi.ini:/etc/uwsgi/uwsgi.ini \
    --detach \
    apigateway:latest
```

### Account Service
1. Create a Docker volume named `pg_account`.
```
sudo docker volume create pg_account
```
2. Run a Docker container based on the official PostgreSQL image. Here we name
the container `account_database`, publish its port 5432 to the host port
5433, set a user named `postgres` with password `postgres` and create a database
`postgres`, enable the `trust` authentication mode, and limit the number of
concurrent connections to 128.
```
sudo docker run \
    --name account_database \
    --publish 5433:5432 \
    --volume pg_account:/var/lib/postgresql/data \
    --env POSTGRES_USER=postgres \
    --env POSTGRES_PASSWORD=postgres \
    --env POSTGRES_DB=postgres \
    --env POSTGRES_HOST_AUTH_METHOD=trust \
    --detach \
    postgres:13.1 \
    -c max_connections=128
```
3. Create tables and indexes.
```
psql -U postgres -h localhost -p 5433 -f app/account/database/account_schema.sql
```
4. Generate Thrift code and copy client libraries.
```
./utils/generate_and_copy_code.sh
```
5. Build the Docker image. Here we name the image `account:latest`.
```
cd app/account/service/server
sudo docker build -t account:latest .
```
6. Run two Docker containers based on the newly built image. Here we name these
containers `account_service1` and `account_service2`, publish their ports 9090
and 9091, respectively, to the same host ports, set the Thrift servers to use 8
threads, and bind-mount the `conf/backend.yml` configuration file in both.
```
cd ../../../..
sudo docker run \
    --name account_service1 \
    --publish 9090:9090 \
    --env port=9090 \
    --env threads=8 \
    --env backend_filepath=/etc/opt/BuzzBlogApp/backend.yml \
    --env postgres_user=postgres \
    --env postgres_password=postgres \
    --env postgres_dbname=postgres \
    --volume $(pwd)/conf/backend.yml:/etc/opt/BuzzBlogApp/backend.yml \
    --detach \
    account:latest
sudo docker run \
    --name account_service2 \
    --publish 9091:9091 \
    --env port=9091 \
    --env threads=8 \
    --env backend_filepath=/etc/opt/BuzzBlogApp/backend.yml \
    --env postgres_user=postgres \
    --env postgres_password=postgres \
    --env postgres_dbname=postgres \
    --volume $(pwd)/conf/backend.yml:/etc/opt/BuzzBlogApp/backend.yml \
    --detach \
    account:latest
```

### Follow Service
1. Generate Thrift code and copy client libraries.
```
./utils/generate_and_copy_code.sh
```
2. Build the Docker image. Here we name the image `follow:latest`.
```
cd app/follow/service/server
sudo docker build -t follow:latest .
```
3. Run a Docker container based on the newly built image. Here we name this
container `follow_service`, publish its port 9092 to the same host port, set
the Thrift server to use 8 threads, and bind-mount the `conf/backend.yml`
configuration file.
```
cd ../../../..
sudo docker run \
    --name follow_service \
    --publish 9092:9092 \
    --env port=9092 \
    --env threads=8 \
    --env backend_filepath=/etc/opt/BuzzBlogApp/backend.yml \
    --env postgres_user=postgres \
    --env postgres_password=postgres \
    --env postgres_dbname=postgres \
    --volume $(pwd)/conf/backend.yml:/etc/opt/BuzzBlogApp/backend.yml \
    --detach \
    follow:latest
```

### Like Service
1. Generate Thrift code and copy client libraries.
```
./utils/generate_and_copy_code.sh
```
2. Build the Docker image. Here we name the image `like:latest`.
```
cd app/like/service/server
sudo docker build -t like:latest .
```
3. Run a Docker container based on the newly built image. Here we name this
container `like_service`, publish its port 9093 to the same host port, set
the Thrift server to use 8 threads, and bind-mount the `conf/backend.yml`
configuration file.
```
cd ../../../..
sudo docker run \
    --name like_service \
    --publish 9093:9093 \
    --env port=9093 \
    --env threads=8 \
    --env backend_filepath=/etc/opt/BuzzBlogApp/backend.yml \
    --env postgres_user=postgres \
    --env postgres_password=postgres \
    --env postgres_dbname=postgres \
    --volume $(pwd)/conf/backend.yml:/etc/opt/BuzzBlogApp/backend.yml \
    --detach \
    like:latest
```

### Post Service
1. Create a Docker volume named `pg_post`.
```
sudo docker volume create pg_post
```
2. Run a Docker container based on the official PostgreSQL image. Here we name
the container `post_database`, publish its port 5432 to the host port
5434, set a user named `postgres` with password `postgres` and create a database
`postgres`, enable the `trust` authentication mode, and limit the number of
concurrent connections to 128.
```
sudo docker run \
    --name post_database \
    --publish 5434:5432 \
    --volume pg_post:/var/lib/postgresql/data \
    --env POSTGRES_USER=postgres \
    --env POSTGRES_PASSWORD=postgres \
    --env POSTGRES_DB=postgres \
    --env POSTGRES_HOST_AUTH_METHOD=trust \
    --detach \
    postgres:13.1 \
    -c max_connections=128
```
3. Create tables and indexes.
```
psql -U postgres -h localhost -p 5434 -f app/post/database/post_schema.sql
```
4. Generate Thrift code and copy client libraries.
```
./utils/generate_and_copy_code.sh
```
5. Build the Docker image. Here we name the image `post:latest`.
```
cd app/post/service/server
sudo docker build -t post:latest .
```
6. Run a Docker container based on the newly built image. Here we name this
container `post_service`, publish its port 9094 to the same host port, set
the Thrift server to use 8 threads, and bind-mount the `conf/backend.yml`
configuration file.
```
cd ../../../..
sudo docker run \
    --name post_service \
    --publish 9094:9094 \
    --env port=9094 \
    --env threads=8 \
    --env backend_filepath=/etc/opt/BuzzBlogApp/backend.yml \
    --env postgres_user=postgres \
    --env postgres_password=postgres \
    --env postgres_dbname=postgres \
    --volume $(pwd)/conf/backend.yml:/etc/opt/BuzzBlogApp/backend.yml \
    --detach \
    post:latest
```

### Uniquepair Service
1. Create a Docker volume named `pg_uniquepair`.
```
sudo docker volume create pg_uniquepair
```
2. Run a Docker container based on the official PostgreSQL image. Here we name
the container `uniquepair_database`, publish its port 5432 to the host port
5435, set a user named `postgres` with password `postgres` and create a database
`postgres`, enable the `trust` authentication mode, and limit the number of
concurrent connections to 128.
```
sudo docker run \
    --name uniquepair_database \
    --publish 5435:5432 \
    --volume pg_uniquepair:/var/lib/postgresql/data \
    --env POSTGRES_USER=postgres \
    --env POSTGRES_PASSWORD=postgres \
    --env POSTGRES_DB=postgres \
    --env POSTGRES_HOST_AUTH_METHOD=trust \
    --detach \
    postgres:13.1 \
    -c max_connections=128
```
3. Create tables and indexes.
```
psql -U postgres -h localhost -p 5435 -f app/uniquepair/database/uniquepair_schema.sql
```
4. Generate Thrift code and copy client libraries.
```
./utils/generate_and_copy_code.sh
```
5. Build the Docker image. Here we name the image `uniquepair:latest`.
```
cd app/uniquepair/service/server
sudo docker build -t uniquepair:latest .
```
6. Run a Docker container based on the newly built image. Here we name this
container `uniquepair_service`, publish its port 9095 to the same host port, set
the Thrift server to use 8 threads, and bind-mount the `conf/backend.yml`
configuration file.
```
cd ../../../..
sudo docker run \
    --name uniquepair_service \
    --publish 9095:9095 \
    --env port=9095 \
    --env threads=8 \
    --env backend_filepath=/etc/opt/BuzzBlogApp/backend.yml \
    --env postgres_user=postgres \
    --env postgres_password=postgres \
    --env postgres_dbname=postgres \
    --volume $(pwd)/conf/backend.yml:/etc/opt/BuzzBlogApp/backend.yml \
    --detach \
    uniquepair:latest
```

### Recommendation Service
1. Create a Docker volume named mongo_recommendation.
```
sudo docker volume create mongo_recommendation
```

2. Run a Docker container based on the official Mongodb image. Here we name the container recommendation_database, publish its port 27017 to the host port 5436, and limit the number of concurrent connections to 128.
```
sudo docker run \
    --name recommendation_database \
    --publish 5436:27017 \
    --volume mongo_recommendation:/var/lib/mongodb/data \
    --detach \
    mongo:4.4.4-bionic
```

3. Create tables and indexes.
```
mongo localhost:5436 ./app/recommendation/database/recommendation.js
```

4. Generate Thrift code and copy client libraries.
```
./utils/generate_and_copy_code.sh
```

5. Build the Docker image. Here we name the image post:latest.
```
cd app/recommendation/service/server
sudo docker build -t recommendation:latest .
```

6. Run a Docker container based on the newly built image. Here we name this container recommendation_service, publish its port 9096 to the same host port, set the Thrift server to use 8 threads, and bind-mount the conf/backend.yml configuration file.
```
cd ../../../..
sudo docker run \
    --name recommendation_service \
    --publish 9096:9096 \
    --env port=9096 \
    --env threads=8 \
    --env backend_filepath=/etc/opt/BuzzBlogApp/backend.yml \
    --volume $(pwd)/conf/backend.yml:/etc/opt/BuzzBlogApp/backend.yml \
    --detach \
    recommendation:latest
```

## Unit Testing
```
for service in account follow like post uniquepair
do
  export PYTHONPATH=app/$service/service/tests/site-packages/
  python3 app/$service/service/tests/test_$service.py
done
python3 app/apigateway/tests/test_api.py
```
