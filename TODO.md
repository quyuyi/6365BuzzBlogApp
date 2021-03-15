### `app/common/thrift/buzzblog.thrift`
- <s>Define service interface for recommendation</s>
```
service TRecommendationService {
  /* Params:
   *   1. requester_id: id of the account making the request.
   *   2. keyword: filter posts by keyword
   *   3. search_size: limit the search space in the database
   *   4. return_size: limit the return size of the search results
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