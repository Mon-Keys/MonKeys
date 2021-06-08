//  Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "Client.hpp"

// Report a failure
void failClient(beast::error_code ec, char const* what) {
  std::cerr << what << ": " << ec.message() << "\n";
}

template <class Body, class Allocator, class Send>
void sendRequest(beast::error_code ec,
                 http::request<Body, http::basic_fields<Allocator>>&& req,
                 Send&& send) {
  if (!strcmp(req.target().data(), "/registr")) {
    std::string login;
    std::cin >> login;
    std::string password;
    std::cin >> password;
    std::string email;
    std::cin >> email;

    property_tree::ptree reqData;
    reqData.put("login", login);
    reqData.put("password", password);
    reqData.put("email", email);
    property_tree::write_json("client.json", reqData);
  }

  if (!strcmp(req.target().data(), "/auth")) {
    std::string login;
    std::cin >> login;
    std::string password;
    std::cin >> password;

    property_tree::ptree reqData;
    reqData.put("login", login);
    reqData.put("password", password);
    property_tree::write_json("client.json", reqData);
  }

  // Attempt to open the file
  http::file_body::value_type body;
  std::string path = "client.json";
  body.open(path.c_str(), beast::file_mode::scan, ec);

  req.body() = std::move(body);

  auto const size = body.size();

  req.content_length(size);

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
  req_.set(http::field::access_control_allow_origin, "http://localhost:3000");

  // Look up the domain login
  resolver_.async_resolve(host, port,
                          beast::bind_front_handler(&ClientSession::on_resolve,
                                                    shared_from_this()));
}

void ClientSession::on_resolve(beast::error_code ec,
                               tcp::resolver::results_type results) {
  if (ec) {
    return failClient(ec, "resolve");
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
    return failClient(ec, "connect");
  }

  // Set a timeout on the operation
  stream_.expires_after(std::chrono::seconds(30));

  sendRequest(ec, std::move(req_), lambda_);
}

void ClientSession::on_write(bool close, beast::error_code ec,
                             std::size_t bytes_transferred) {
  boost::ignore_unused(bytes_transferred);

  if (ec) {
    return failClient(ec, "write");
  }

  reqsp_ = nullptr;

  do_read();
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
    return failClient(ec, "read");
  }

  // Write the message to standard out
  property_tree::ptree resJson;
  std::stringstream jsonStream(res_.body());
  property_tree::read_json(jsonStream, resJson);

  property_tree::ptree clientJson;
  property_tree::read_json("client.json", clientJson);
  std::string password = clientJson.get<std::string>("password");
  resJson.put("password", password);
  resJson.erase("status");

  property_tree::write_json("client.json", resJson);

  std::cout << res_ << std::endl;

  // Gracefully close the socket
  stream_.socket().shutdown(tcp::socket::shutdown_both, ec);

  // not_connected happens sometimes so don't bother reporting it.
  if (ec && ec != beast::errc::not_connected) {
    return failClient(ec, "shutdown");
  }

  // If we get here then the connection is closed gracefully
}
