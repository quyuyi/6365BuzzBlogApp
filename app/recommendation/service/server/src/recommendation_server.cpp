// Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
// Systems

#include <string>

#include <cxxopts.hpp>

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>

#include <buzzblog/gen/TRecommendationService.h>
#include <buzzblog/base_server.h>


using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace gen;


class TRecommendationServiceHandler : public BaseServer, public TRecommendationServiceIf {
private:

public:
  TRecommendationServiceHandler(const std::string& backend_filepath,
      const std::string& postgres_user, const std::string& postgres_password,
      const std::string& postgres_dbname)
  : BaseServer(backend_filepath, postgres_user, postgres_password,
      postgres_dbname) {
        mongocxx::instance instance{}; // This should be done only once.
  }

  void retrieve_recommended_posts(std::vector<TRecPost> & _return, 
                                  const std::string& keyword, 
                                  const int32_t search_size, 
                                  const int32_t return_size) {
    // Connect to mongodb
    mongocxx::uri uri(recommendation_db_conn_url);
    mongocxx::client client(uri);
    mongocxx::database db = client["myDatabase"];
    mongocxx::collection collection = db["recommendations"];

    // create index for keywords
    // https://docs.mongodb.com/manual/core/index-multikey/
    // auto index_value = document{} << "keywords" << 1 << finalize;
    // collection.create_index(index_value.view());

    // query by one keyword
    auto query_value = document{} << "keywords" << keyword << finalize;
    mongocxx::options::find opts;
    opts.limit(return_size);
    mongocxx::cursor cursor = collection.find(query_value.view(), opts);
    std::cout << "Printing posts with keyword " << keyword << std::endl;

    // Build result list.
    for (auto doc : cursor)
    {
        std::cout << bsoncxx::to_json(doc) << "\n";
        TRecPost p;
        p.post_id = doc["post_id"].get_int32();
        p.tweet_id = doc["tweet_id"].get_utf8().value.to_string();
        p.created_at = doc["created_at"].get_utf8().value.to_string();
        p.text = doc["text"].get_utf8().value.to_string();
        bsoncxx::array::view keywords{doc["keywords"].get_array().value};
        for (const bsoncxx::array::element& keyword : keywords) {
            p.keywords.push_back(keyword.get_utf8().value.to_string());
        }
        _return.push_back(p);
    }
    
  }
  
};


int main(int argc, char** argv) {
  // Define command-line parameters.
  cxxopts::Options options("recommendation_server", "Recommendation server");
  options.add_options()
      ("host", "", cxxopts::value<std::string>()->default_value("0.0.0.0"))
      ("port", "", cxxopts::value<int>())
      ("threads", "", cxxopts::value<int>())
      ("backend_filepath", "", cxxopts::value<std::string>()->default_value(
          "/etc/opt/BuzzBlogApp/backend.yml"))
      ("postgres_user", "", cxxopts::value<std::string>()->default_value(
          "postgres"))
      ("postgres_password", "", cxxopts::value<std::string>()->default_value(
          "postgres"))
      ("postgres_dbname", "", cxxopts::value<std::string>()->default_value(
          "postgres"));

  // Parse command-line arguments.
  auto result = options.parse(argc, argv);
  std::string host = result["host"].as<std::string>();
  int port = result["port"].as<int>();
  int threads = result["threads"].as<int>();
  std::string backend_filepath = result["backend_filepath"].as<std::string>();
  std::string postgres_user = result["postgres_user"].as<std::string>();
  std::string postgres_password = result["postgres_password"].as<std::string>();
  std::string postgres_dbname = result["postgres_dbname"].as<std::string>();

  // Create server.
  TThreadedServer server(
      std::make_shared<TRecommendationServiceProcessor>(
          std::make_shared<TRecommendationServiceHandler>(backend_filepath,
              postgres_user, postgres_password, postgres_dbname)),
      std::make_shared<TServerSocket>(host, port),
      std::make_shared<TBufferedTransportFactory>(),
      std::make_shared<TBinaryProtocolFactory>());
  server.setConcurrentClientLimit(threads);

  // Serve requests.
  server.serve();

  return 0;
}