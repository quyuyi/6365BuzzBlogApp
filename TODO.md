## TODO
### `app/common/thrift/buzzblog.thrift`
- <s>Define service interface for recommendation</s>
```thrift
struct TRecPost {
  1: required i32 post_id;
  2: required string tweet_id;
  3: required i32 created_at;
  4: required string text;
  5: required list<string> keywords;
}

service TRecommendationService {
  /* Params:
   *   1. keyword: filter posts by keyword
   *   2. search_size: limit the search space in the database
   *   3. return_size: limit the return size of the search results
   * Returns:
   *   A list of posts (standard mode) containing the keyword.
   */
  list<TRecPost> retrieve_recommended_posts (1:string keyword);
}
```

- will add parameter 3 and 4 later, first implement the basic functionality

### `app/recommendation/service/`
- `app/recommendation/service/server/src/recommendation_server.cpp`
    - <s>Change pqxx to mongocxx</s>
    - <s>Implement TRecommendationServiceHandler generated and will be used by thrift</s>
    - <s>Add to base server for mongodb connection and recommendation configuration</s>

- `app/recommendation/service/client/src/recommendation_client.<cpp|py>`
    - <s>Implement service client to be able to use the server functions</s>

- `app/recommendation/service/tests/test_recommendation.<cpp|py>`
    - <s>Test as a server client</s>

- `app/common/include/base_server.h`

### `app/recommendation/database/`
- <s>Execution code for mongodb when initializing the server. I.e., create table, ...</s>

### `app/recommendation/service/server/Dockerfile`
- <s>Define the image for the recommendation server</s>
- <s>Compile and execution code to start the server</s> NOT TESTED

### `app/apigateway/serber/src/apigateway.py`
- <s>Add end point for recommendation service</s>

### Compile and run
```
APPDIR=$PWD
cd app/recommendation/service/server/
mkdir bin
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
```


## Mongodb
Start mongodb, open cli, stop mongodb.
```bash
sudo systemctl start mongod
mongo
sudo systemctl stop mongod
```

Data Modeling
- Basically it is a collection of one document. 
(A collection is the equivalent of an RDBMS table. A collection exists within a single database. 
Collections do not enforce a schema. Documents within a collection can have different fields. 
Typically, all documents in a collection have a similar or related purpose.)

- The document is defined as:
```
{
  "object": "post",
  "id": 123,
  "created_at": 1601912233,
  "text": "Hello, world.",
  "topics" : ["Sports", "Hobby"],
}
```

Query
- Example Query
```
use myNewDB
db.myNewCollection1.insertMany( [post_info1, post_info2,...] )
db.collection.find({ "topics": "Sports" }).limit(return_size)
db.collection.find( { topics: { $all: [ "Sports", "Hobby" ] }, "created_at": {"$gt": after_date} } ).limit(return_size)
```

- Question
    - How to query based on search_size?

- Query Documents
    - https://docs.mongodb.com/manual/reference/method/db.collection.find/#db.collection.find
    - https://docs.mongodb.com/manual/tutorial/query-documents/#read-operations-query-argument
  

### Deployment and Test
- No need to deploy 


## Notes
Run mongodb on docker; check docker should have a mongodb image

## Dataset
- Extract keywords:\
Summerization, but need long context -> twitter post is too small.\
Better to simplify\
Create a dictionay of words ~100 words. Or count the most 100 popular words from the dataset.\
The goal is to introduce variability.\

