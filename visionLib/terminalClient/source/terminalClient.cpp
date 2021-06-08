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
    std::string companyName = confData.get<std::string>("companyName");
    std::string licenseKey = confData.get<std::string>("licenseKey");

    property_tree::ptree reqData;
    reqData.put("timecode", timecode);
    reqData.put("companyName", companyName);
    reqData.put("licenseKey", licenseKey);
    property_tree::write_json("terminal.json", reqData);
  }

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
  auto sp =
      std::make_shared<http::message<isRequest, Body, Fields>>(std::move(msg));

  self_.reqsp_ = sp;

  http::async_write(
      self_.stream_, *sp,
      beast::bind_front_handler(&TerminalSession::on_write,
                                self_.shared_from_this(), sp->need_eof()));
}

void TerminalSession::run(char const* host, char const* port,
                          std::string target, int version,
                          const std::string& currentTimecode) {
  req_.version(version);
  req_.method(http::verb::post);
  req_.target(target);
  req_.set(http::field::host, host);
  req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  timecode_ = currentTimecode;

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

  stream_.expires_after(std::chrono::seconds(30));

  stream_.async_connect(results,
                        beast::bind_front_handler(&TerminalSession::on_connect,
                                                  shared_from_this()));
}

void TerminalSession::on_connect(beast::error_code ec,
                                 tcp::resolver::results_type::endpoint_type) {
  if (ec) {
    return failTerminal(ec, "connect");
  }

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
  res_ = {};

  stream_.expires_after(std::chrono::seconds(30));

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

  property_tree::ptree resJson;
  std::stringstream jsonStream(res_.body());
  property_tree::read_json(jsonStream, resJson);
  std::cout << "check" << std::endl;

  std::string verification = "";
  try {
    verification = resJson.get<std::string>("verification");
  } catch (...) {
    std::cout << "no verification";
    verification = "failure";
  }
  std::cout << "check" << std::endl;
  if (!std::strcmp(verification.c_str(), "success")) {
    system("clear");

    std::cout << "access open\n";
  } else {
    system("clear");

    std::cout << "access closed\n";
  }

  stream_.socket().shutdown(tcp::socket::shutdown_both, ec);

  if (ec && ec != beast::errc::not_connected) {
    return failTerminal(ec, "shutdown");
  }

}
