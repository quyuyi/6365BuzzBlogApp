### `app/common/thrift/buzzblog.thrift`
- Define service interface for recommendation

### `app/recommendation/service/`
- `app/recommendation/service/server/src/recommendation_server.cpp`
    - Implement TRecommendationServiceHandler generated and will be used by thrift
    - Implement main function for server

- `app/recommendation/service/client/src/recommendation_client.<cpp|py>`
    - Implement service client to be able to use the server functions

- `app/recommendation/service/tests/test_recommendation.<cpp|py>`
    - Test as a server client
    - Question: no implementation for cpp in current repo? Can implement our client in py? need to implement the `client/src/recommendation_client.cpp`?

### `app/recommendation/database/`
- Execution code for mongodb when initializing the server. I.e., create table, ...

### `app/recommendation/service/server/Dockerfile`
- Defile image for the recommendation server
- Compile and execution code to start the server