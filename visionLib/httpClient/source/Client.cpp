// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "Client.hpp"

Client::Client() {}
Client::Client(uint64_t _ID, Pass* _passes, uint16_t _passesCount,
               std::string _name, std::string _password, bool _isConnected,
               bool _isLogin) {}
Client::~Client() {}

void Client::logIn() {}
void Client::logOut() {}
void Client::registerClient() {}
void Client::requestPasses() {}
std::string Client::getTempPass(uint64_t passID) { return ""; }

void Client::establishConnection(const char* url) {}
void Client::breakConnection() {}

uint64_t Client::getID() { return 1; }
Client::Pass* Client::getPasses() {
  Pass* currentPasses = nullptr;
  return currentPasses;
}
uint16_t Client::getPassesCount() { return 1; }
std::string Client::getName() { return ""; }
bool Client::getIsConnected() { return false; }
bool Client::getIsLogIn() { return false; }
Client::Pass Client::getPass(uint64_t index) { return Pass(); }

void Client::setID(uint64_t ID) {}
void Client::setPasses(Pass* currentPasses) {}
void Client::setPassesCount(uint16_t _passesCount) {}
void Client::setName(std::string _name) {}
void Client::setIsConnected(const bool value) {}
void Client::setIsLogIn(const bool value) {}

Client::Pass::Pass() {}
// cppcheck-suppress uninitMemberVar
Client::Pass::Pass(uint64_t _ID, std::string _privateKey,
                   std::string _companyName) {}
Client::Pass::~Pass() {}

std::string Client::Pass::requestTempCode() { return ""; }
void Client::Pass::getID() {}
void Client::Pass::getPrivateKey() {}
void Client::Pass::getCompanyName() {}
void Client::Pass::setID(uint64_t ID) {}
void Client::Pass::setPrivateKey(std::string _privateKey) {}
void Client::Pass::setCompanyName(std::string _companyName) {}

// Report a failure
void failOnClient(beast::error_code ec, char const* what) {
  std::cerr << what << ": " << ec.message() << "\n";
}

template <class Body, class Allocator, class Send>
void sendRequest(beast::error_code ec,
                 http::request<Body, http::basic_fields<Allocator>>&& req,
                 Send&& send) {
  property_tree::ptree bodyData;
  bodyData.put("name", "Mikhail");
  bodyData.put("password", "hello123");
  property_tree::write_json("client.json", bodyData);

  // Attempt to open the file
  // http::file_body::value_type body;
  // std::string path = "client.json";
  // body.open(path.c_str(), beast::file_mode::scan, ec);

  // req.body() = std::move(body);

  std::ifstream file("client.json");
  std::string line;
  std::string body;
  while (std::getline(file, line)) {
    body += line;
  }

  req.body() = std::move(body);

  // auto const size = body.size();

  // http::request<http::file_body> res{
  //                                std::piecewise_construct,
  //                                std::make_tuple(std::move(body)),
  //                                std::make_tuple(http::status::ok,
  //                                req.version())};
  // res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
  // res.set(http::field::content_type, "application/json");
  // res.content_length(size);
  // res.keep_alive(req.keep_alive());

  return send(std::move(req));
}

template <bool isRequest, class Body, class Fields>
void ClientSession::send_lambda::operator()(
    http::message<isRequest, Body, Fields>&& msg) const {
  // The lifetime of the message has to extend
  // for the duration of the async operation so
  // we use a shared_ptr to manage it.
  auto sp =
      std::make_shared<http::message<isRequest, Body, Fields>>(std::move(msg));

  // Store a type-erased version of the shared
  // pointer in the class to keep it alive.
  self_.reqsp_ = sp;

  // Write the response
  http::async_write(
      self_.stream_, *sp,
      beast::bind_front_handler(&ClientSession::on_write,
                                self_.shared_from_this(), sp->need_eof()));
}

// Start the asynchronous operation
void ClientSession::run(char const* host, char const* port, char const* target,
                        int version) {
  // Set up an HTTP GET request message
  req_.version(version);
  req_.method(http::verb::post);
  req_.target(target);
  req_.set(http::field::host, host);
  req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

  // Look up the domain name
  resolver_.async_resolve(host, port,
                          beast::bind_front_handler(&ClientSession::on_resolve,
                                                    shared_from_this()));
}

void ClientSession::on_resolve(beast::error_code ec,
                               tcp::resolver::results_type results) {
  if (ec) {
    return failOnClient(ec, "resolve");
  }

  // Set a timeout on the operation
  stream_.expires_after(std::chrono::seconds(30));

  // Make the connection on the IP address we get from a lookup
  stream_.async_connect(results,
                        beast::bind_front_handler(&ClientSession::on_connect,
                                                  shared_from_this()));
}

void ClientSession::on_connect(beast::error_code ec,
                               tcp::resolver::results_type::endpoint_type) {
  if (ec) {
    return failOnClient(ec, "connect");
  }

  // Set a timeout on the operation
  stream_.expires_after(std::chrono::seconds(30));

  // property_tree::ptree bodyData;
  // bodyData.put("name", "Mikhail");
  // bodyData.put("password", "hello123");
  // property_tree::write_json("client.json", bodyData);

  // // Attempt to open the file
  // http::file_body::value_type body;
  // std::string path = "client.json";
  // body.open(path.c_str(), beast::file_mode::scan, ec);

  // req_.body() = std::move(body);

  sendRequest(ec, std::move(req_), lambda_);

  // Send the HTTP request to the remote host
  // http::async_write(stream_, req_,
  // beast::bind_front_handler(&ClientSession::on_write, shared_from_this()));
}

void ClientSession::on_write(bool close, beast::error_code ec,
                             std::size_t bytes_transferred) {
  boost::ignore_unused(bytes_transferred);

  if (ec) {
    return failOnClient(ec, "write");
  }

  reqsp_ = nullptr;

  do_read();

  // Receive the HTTP response
  // http::async_read(stream_, buffer_, res_,
  // beast::bind_front_handler(&ClientSession::on_read, shared_from_this()));
}

void ClientSession::do_read() {
  // Make the request empty before reading,
  // otherwise the operation behavior is undefined.
  res_ = {};

  // Set the timeout.
  stream_.expires_after(std::chrono::seconds(30));

  // Read a request
  http::async_read(
      stream_, buffer_, res_,
      beast::bind_front_handler(&ClientSession::on_read, shared_from_this()));
}

void ClientSession::on_read(beast::error_code ec,
                            std::size_t bytes_transferred) {
  boost::ignore_unused(bytes_transferred);

  if (ec) {
    return failOnClient(ec, "read");
  }

  // Write the message to standard out
  property_tree::ptree resJson;
  // std::stringstream jsonStream(res_.body());
  // property_tree::read_json(jsonStream, resJson);
  // std::string imageSource = resJson.get<std::string>("widget.image.src");
  // int textSize = resJson.get<int>("widget.text.size");
  // std::cout << imageSource << " " << textSize << "\n";
  std::cout << res_ << std::endl;

  // Gracefully close the socket
  stream_.socket().shutdown(tcp::socket::shutdown_both, ec);

  // not_connected happens sometimes so don't bother reporting it.
  if (ec && ec != beast::errc::not_connected) {
    return failOnClient(ec, "shutdown");
  }

  // If we get here then the connection is closed gracefully
}
