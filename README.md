# BuzzBlog
BuzzBlog is an open-source microblogging application that follows the
microservice architectural style. As with Twitter, users can write short posts,
follow other users, and like their favorite posts.

BuzzBlog is part of
[Wise](https://www.cc.gatech.edu/systems/projects/Elba/Wise/), a toolkit for the
experimental study of systems performance. In particular, BuzzBlog was developed
for the study of long tail latency in microservice architectures caused by
resource bottlenecks in the order of milliseconds.

BuzzBlog was developed by Rodrigo Alves Lima (<ral@gatech.edu>) and is licensed
under the [Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0).

## Architecture
### Load Balancer
An NGINX server is deployed as a load balancer in front of API Gateway servers.
Client requests first arrive at the NGINX server, which then chooses one of the
API Gateway servers to forward each request based on a load-balancing algorithm
(for example, Round Robin).

### API Gateway
The API Gateway sits between the load balancer that receives requests from the
clients and the backend services needed to fulfill these requests. It receives
HTTP requests (forwarded by the load balancer) representing calls to the
BuzzBlog API, makes RPCs to the backend services, and replies HTTP responses
containing JSON-encoded data.

To learn how to build HTTP requests representing calls to the BuzzBlog API and
what to expect as response, see the [BuzzBlog API Reference](docs/API.md).
It lists all API endpoints available, their parameters, and their response data
format.

### Backend Services
The backend services have small scope, conforming to the microservice
architectural style. Four services implement business capabilities: *account* is
responsible for user authentication and account management, *post* for posting,
*like* for post liking, and *follow* for user following. The other service,
*uniquepair*, implements an abstract data type (sets of unique pairs).

### Data Storage
Backend services *account*, *post*, and *uniquepair* store data in PostgreSQL
databases, while *follow* and *like* have their data managed by the *uniquepair*
service.

## Request Lifecycle
BuzzBlog has an API organized around REST, using standard HTTP methods and
authentication to access and manipulate objects through predictable URLs.

A call to the BuzzBlog API starts with the client sending an HTTP request to the
NGINX server that acts as load balancer. This request is then forwarded to an
API Gateway server chosen by a load-balancing algorithm (for example, Round
Robin).

Upon the arrival of this HTTP request, the API Gateway selects the
proper request handler based on the URL path and HTTP method, as defined in the
[BuzzBlog API Reference](docs/API.md). For example, an HTTP request whose method
is `GET` and URL path is `/account/:account_id` will be handled by
`retrieve_account` (see `app/apigateway/server/src/apigateway.py`).

Such a request handler accesses and manipulates objects through RPCs to the
backend services. For example, `retrieve_account` retrieves account information
by calling the method `retrieve_expanded_account` of the *account* service (see
`app/account/service/server/src/account_server.cpp`).

These backend services commonly call each other to retrieve and update data, and
some of them also query databases. For example, `retrieve_expanded_account`
queries a PostgreSQL database to retrieve account information and calls services
*post*, *like*, and *follow* to retrieve a summary of the posting, liking, and
following activities of that account, respectively.

The request handler replies an HTTP response (containing JSON-encoded
data) based on the results of the RPCs made to the backend services, which is
finally sent back to the client by the load balancer.
