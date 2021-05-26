// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "terminalClient.hpp"

bool exists(const std::string& name) {
  struct stat buffer;
  return (stat(name.c_str(), &buffer) == 0);
}

// Report a failTerminalure
void failTerminal(beast::error_code ec, char const* what) {
  std::cerr << what << ": " << ec.message() << "\n";
}

void createConfigFile() {
  bool exist = exists("config.json");
  property_tree::ptree confData;
  if (!exist) {
    std::string companyName;
    std::string licenseKey;
    std::cout << "-------------------Начальная настройка-------------------\n"
              << "Введите вашу название вашей компании и лицензионный ключ:\n";
    std::cin >> companyName;
    std::cin >> licenseKey;

    std::ofstream ofs("config.json");
    ofs.close();

    confData.put("companyName", companyName);
    confData.put("licenseKey", licenseKey);
    property_tree::write_json("config.json", confData);
  }
}

template <class Body, class Allocator, class Send>
void sendTerminalRequest(
    beast::error_code ec,
    http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send,
    const std::string& timecode) {
  property_tree::ptree confData;
  property_tree::read_json("config.json", confData);

  if (!strcmp(req.target().data(), "/checktimecode")) {
    // std::string timecode;
    // std::cin >> timecode;
    std::string companyName = confData.get<std::string>("companyName");
    std::string licenseKey = confData.get<std::string>("licenseKey");

    property_tree::ptree reqData;
    reqData.put("timecode", timecode);
    reqData.put("companyName", companyName);
    reqData.put("licenseKey", licenseKey);
    property_tree::write_json("terminal.json", reqData);
  }

  // Attempt to open the file
  http::file_body::value_type body;
  std::string path = "terminal.json";
  body.open(path.c_str(), beast::file_mode::scan, ec);

  req.body() = std::move(body);

  auto const size = body.size();

  req.content_length(size);

  return send(std::move(req));
}

template <bool isRequest, class Body, class Fields>
void TerminalSession::send_lambda::operator()(
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
      beast::bind_front_handler(&TerminalSession::on_write,
                                self_.shared_from_this(), sp->need_eof()));
}

// Start the asynchronous operation
void TerminalSession::run(char const* host, char const* port,
                          std::string target, int version,
                          const std::string& currentTimecode) {
  // Set up an HTTP GET request message
  req_.version(version);
  req_.method(http::verb::post);
  req_.target(target);
  req_.set(http::field::host, host);
  req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  timecode_ = currentTimecode;

  // Look up the domain name
  resolver_.async_resolve(
      host, port,
      beast::bind_front_handler(&TerminalSession::on_resolve,
                                shared_from_this()));
}

void TerminalSession::on_resolve(beast::error_code ec,
                                 tcp::resolver::results_type results) {
  if (ec) {
    return failTerminal(ec, "resolve");
  }

  // Set a timeout on the operation
  stream_.expires_after(std::chrono::seconds(30));

  // Make the connection on the IP address we get from a lookup
  stream_.async_connect(results,
                        beast::bind_front_handler(&TerminalSession::on_connect,
                                                  shared_from_this()));
}

void TerminalSession::on_connect(beast::error_code ec,
                                 tcp::resolver::results_type::endpoint_type) {
  if (ec) {
    return failTerminal(ec, "connect");
  }

  // Set a timeout on the operation
  stream_.expires_after(std::chrono::seconds(30));

  sendTerminalRequest(ec, std::move(req_), lambda_, timecode_);
}

void TerminalSession::on_write(bool close, beast::error_code ec,
                               std::size_t bytes_transferred) {
  boost::ignore_unused(bytes_transferred);

  if (ec) {
    return failTerminal(ec, "write");
  }

  reqsp_ = nullptr;

  do_read();
}

void TerminalSession::do_read() {
  // Make the request empty before reading,
  // otherwise the operation behavior is undefined.
  res_ = {};

  // Set the timeout.
  stream_.expires_after(std::chrono::seconds(30));

  // Read a request
  http::async_read(
      stream_, buffer_, res_,
      beast::bind_front_handler(&TerminalSession::on_read, shared_from_this()));
}

void TerminalSession::on_read(beast::error_code ec,
                              std::size_t bytes_transferred) {
  boost::ignore_unused(bytes_transferred);

  if (ec) {
    return failTerminal(ec, "read");
  }

  // Write the message to standard out
  property_tree::ptree resJson;
  std::stringstream jsonStream(res_.body());
  property_tree::read_json(jsonStream, resJson);

  std::string verification = resJson.get<std::string>("verification");
  if (!std::strcmp(verification.c_str(), "success")) {
    system("clear");

    std::cout << "access open\n";
  } else {
    system("clear");

    std::cout << "access closed\n";
  }

  // Gracefully close the socket
  stream_.socket().shutdown(tcp::socket::shutdown_both, ec);

  // not_connected happens sometimes so don't bother reporting it.
  if (ec && ec != beast::errc::not_connected) {
    return failTerminal(ec, "shutdown");
  }

  // If we get here then the connection is closed gracefully
}
