### `app/common/thrift/buzzblog.thrift`
- <s>Define service interface for recommendation</s>
```
service TRecommendationService {
  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. keyword(s): filter posts by keyword(s)
   *   3. search_size: limit the search space in the database
   *   4. return_size: limit the return size of the search results
   *   5. after_date: limit the post created time after a certain date
   * Returns:
   *   A list of posts (standard mode) containing the keyword.
   */
  list<TPost> retrieve_recommended_posts (1:i32 requester_id, 2:string keyword);
}
```
- Questions
    - maybe we don't even need to the requester id
    - return posts in standard mode ot expanded mode
    - will add parameter 3 and 4 later, first implement the basic functionality

### `app/recommendation/service/`
- `app/recommendation/service/server/src/recommendation_server.cpp`
    - Change pqxx to mongocxx
    - Implement TRecommendationServiceHandler generated and will be used by thrift
    - Change main function for server

- `app/recommendation/service/client/src/recommendation_client.<cpp|py>`
    - Implement service client to be able to use the server functions

- `app/recommendation/service/tests/test_recommendation.<cpp|py>`
    - Test as a server client
    - Question: no implementation for cpp in current repo? Can implement our client in py? need to implement the `client/src/recommendation_client.cpp`?

### `app/recommendation/database/`
- Execution code for mongodb when initializing the server. I.e., create table, ...
- Question: use mongodb for recommendation storage; use postgres for account/post/... storage. If we want to use account services, we still need the postgres db. \
Or do we change the existing services to migrate the storage to mongodb?

### `app/recommendation/service/server/Dockerfile`
- <s>Define the image for the recommendation server</s>
- Compile and execution code to start the server

### `app/apigateway/serber/src/apigateway.py`
- Add end point for recommendation service


## Mongodb
Start mongodb, open cli, stop mongodb.
```
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
  "mode": "expanded",(delete?)
  "id": 123,
  "created_at": 1601912233,
  "active": true,(delete?)
  "text": "Hello, world.",
  "topics" : ["Sports", "Hobby"],
  "author_id": 12345,
  "author": {
    "object": "account",
    "mode": "standard",
    "id": 12345,
    "created_at": 1601912233,
    "active": true,
    "username": "john.doe",
    "first_name": "John",
    "last_name": "Doe"
  },(delete?)
  "n_likes": 0(delete?)
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
    