// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "httpServer.hpp"

#include "clientHandler.hpp"

beast::string_view mime_type(beast::string_view path) {
  using beast::iequals;
  auto const ext = [&path] {
    auto const pos = path.rfind(".");
    if (pos == beast::string_view::npos) return beast::string_view{};
    return path.substr(pos);
  }();
  if (iequals(ext, ".htm")) return "text/html";
  if (iequals(ext, ".html")) return "text/html";
  if (iequals(ext, ".php")) return "text/html";
  if (iequals(ext, ".css")) return "text/css";
  if (iequals(ext, ".txt")) return "text/plain";
  if (iequals(ext, ".js")) return "application/javascript";
  if (iequals(ext, ".json")) return "application/json";
  if (iequals(ext, ".xml")) return "application/xml";
  if (iequals(ext, ".swf")) return "application/x-shockwave-flash";
  if (iequals(ext, ".flv")) return "video/x-flv";
  if (iequals(ext, ".png")) return "image/png";
  if (iequals(ext, ".jpe")) return "image/jpeg";
  if (iequals(ext, ".jpeg")) return "image/jpeg";
  if (iequals(ext, ".jpg")) return "image/jpeg";
  if (iequals(ext, ".gif")) return "image/gif";
  if (iequals(ext, ".bmp")) return "image/bmp";
  if (iequals(ext, ".ico")) return "image/vnd.microsoft.icon";
  if (iequals(ext, ".tiff")) return "image/tiff";
  if (iequals(ext, ".tif")) return "image/tiff";
  if (iequals(ext, ".svg")) return "image/svg+xml";
  if (iequals(ext, ".svgz")) return "image/svg+xml";
  return "application/text";
}

std::string path_cat(beast::string_view base, beast::string_view path) {
  if (base.empty()) {
    return std::string(path);
  }
  std::string result(base);
#ifdef BOOST_MSVC
  char constexpr path_separator = '\\';
  if (result.back() == path_separator) result.resize(result.size() - 1);
  result.append(path.data(), path.size());
  for (auto& c : result)
    if (c == '/') c = path_separator;
#else
  char constexpr path_separator = '/';
  if (result.back() == path_separator) {
    result.resize(result.size() - 1);
  }
  result.append(path.data(), path.size());
#endif
  return result;
}

template <class Body, class Allocator, class Send>
void handle_request(beast::string_view doc_root,
                    http::request<Body, http::basic_fields<Allocator>>&& req,
                    Send&& send) {
  if (req.method() == http::verb::options) {
    http::response<http::empty_body> res{http::status::no_content,
                                         req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.keep_alive(req.keep_alive());
    res.set(http::field::access_control_allow_origin, "*");
    res.set(http::field::access_control_allow_methods, "POST");
    res.set(http::field::access_control_allow_headers, "Content-Type");
    return send(std::move(res));
  }
  auto const bad_request = [&req](beast::string_view why) {
    http::response<http::string_body> res{http::status::bad_request,
                                          req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    res.keep_alive(req.keep_alive());
    res.body() = std::string(why);
    res.prepare_payload();
    return res;
  };

  auto const not_found = [&req](beast::string_view target) {
    http::response<http::string_body> res{http::status::not_found,
                                          req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    res.keep_alive(req.keep_alive());
    res.body() = "The resource '" + std::string(target) + "' was not found.";
    res.prepare_payload();
    return res;
  };

  auto const server_error = [&req](beast::string_view what) {
    http::response<http::string_body> res{http::status::internal_server_error,
                                          req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    res.keep_alive(req.keep_alive());
    res.body() = "An error occurred: '" + std::string(what) + "'";
    res.prepare_payload();
    return res;
  };

  if (req.method() != http::verb::post && req.method() != http::verb::head &&
      req.method() != http::verb::options)
    return send(bad_request("Unknown HTTP-method"));

  if (req.target().empty() || req.target()[0] != '/' ||
      req.target().find("..") != beast::string_view::npos)
    return send(bad_request("Illegal request-target"));

  clientHandler currentHandler;

  std::string path;
  std::string jsonName;
  if (!strcmp(req.target().data(), "/registr")) {
    property_tree::ptree reqJson;
    std::stringstream jsonStream(req.body());
    property_tree::read_json(jsonStream, reqJson);
    try {
      std::string login = reqJson.get<std::string>("login");
      std::string password = reqJson.get<std::string>("password");
      std::string email = reqJson.get<std::string>("email");

      jsonName = currentHandler.registerClient(login, email, password);
    } catch (const std::exception& exc) {
      std::cout << exc.what();
    }

  } else if (!strcmp(req.target().data(), "/auth")) {
    property_tree::ptree reqJson;
    std::stringstream jsonStream(req.body());
    property_tree::read_json(jsonStream, reqJson);

    try {
      std::string login = reqJson.get<std::string>("login");
      std::string password = reqJson.get<std::string>("password");

      jsonName = currentHandler.logInClient(login, password);
    } catch (const std::exception& exc) {
      std::cout << exc.what();
    }
  } else if (!strcmp(req.target().data(), "/timecode")) {
    property_tree::ptree reqJson;
    std::stringstream jsonStream(req.body());
    property_tree::read_json(jsonStream, reqJson);
    try {
      std::string login = reqJson.get<std::string>("login");
      std::string password = reqJson.get<std::string>("password");

      jsonName = currentHandler.getTimeCode(login, password);
    } catch (const std::exception& exc) {
      std::cout << exc.what();
    }
  } else if (!strcmp(req.target().data(), "/admin")) {
    property_tree::ptree reqJson;
    std::stringstream jsonStream(req.body());
    property_tree::read_json(jsonStream, reqJson);
    try {
      std::string companyName = reqJson.get<std::string>("companyName");
      std::string licenseKey = reqJson.get<std::string>("licenseKey");

      jsonName = currentHandler.logInAdmin(companyName, licenseKey);
    } catch (const std::exception& exc) {
      std::cout << exc.what();
    }
  } else if (!strcmp(req.target().data(), "/addpass")) {
    property_tree::ptree reqJson;
    std::stringstream jsonStream(req.body());
    property_tree::read_json(jsonStream, reqJson);
    try {
      std::string companyName = reqJson.get<std::string>("companyName");
      std::string login = reqJson.get<std::string>("login");

      jsonName = currentHandler.addCleintsPass(login, companyName);
    } catch (const std::exception& exc) {
      std::cout << exc.what();
    }
  }
  path = path_cat(doc_root, "/");
  path.append(jsonName);

  beast::error_code ec;
  http::file_body::value_type body;
  body.open(path.c_str(), beast::file_mode::scan, ec);

  if (ec == beast::errc::no_such_file_or_directory) {
    return send(not_found(req.target()));
  }

  if (ec) {
    return send(server_error(ec.message()));
  }

  auto const size = body.size();

  std::cout << req << std::endl;

  if (req.method() == http::verb::head) {
    http::response<http::empty_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, mime_type(path));
    res.content_length(size);
    res.keep_alive(req.keep_alive());
    res.set(http::field::access_control_allow_origin, "*");
    return send(std::move(res));
  }

  http::response<http::file_body> res{
      std::piecewise_construct, std::make_tuple(std::move(body)),
      std::make_tuple(http::status::ok, req.version())};
  res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
  res.set(http::field::content_type, mime_type(path));
  res.content_length(size);
  res.keep_alive(req.keep_alive());
  res.set(http::field::access_control_allow_origin, "*");
  return send(std::move(res));
}

void failServer(beast::error_code ec, char const* what) {
  std::cerr << what << ": " << ec.message() << "\n";
}

template <bool isRequest, class Body, class Fields>
void ServerSession::send_lambda::operator()(
    http::message<isRequest, Body, Fields>&& msg) const {
  auto sp =
      std::make_shared<http::message<isRequest, Body, Fields>>(std::move(msg));

  self_.res_ = sp;

  http::async_write(
      self_.stream_, *sp,
      beast::bind_front_handler(&ServerSession::on_write,
                                self_.shared_from_this(), sp->need_eof()));
}

void ServerSession::run() {
  net::dispatch(
      stream_.get_executor(),
      beast::bind_front_handler(&ServerSession::do_read, shared_from_this()));
}

void ServerSession::do_read() {
  req_ = {};

  stream_.expires_after(std::chrono::seconds(30));

  http::async_read(
      stream_, buffer_, req_,
      beast::bind_front_handler(&ServerSession::on_read, shared_from_this()));
}

void ServerSession::on_read(beast::error_code ec,
                            std::size_t bytes_transferred) {
  boost::ignore_unused(bytes_transferred);

  if (ec == http::error::end_of_stream) {
    return do_close();
  }

  if (ec) {
    return failServer(ec, "read");
  }

  std::cout << "user connected\n";
  handle_request(*doc_root_, std::move(req_), lambda_);
}

void ServerSession::on_write(bool close, beast::error_code ec,
                             std::size_t bytes_transferred) {
  boost::ignore_unused(bytes_transferred);

  if (ec) {
    return failServer(ec, "write");
  }

  if (close) {
    return do_close();
  }

  res_ = nullptr;

  do_read();
}

void ServerSession::do_close() {
  beast::error_code ec;
  stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
}

void Listener::run() { do_accept(); }

void Listener::do_accept() {
  acceptor_.async_accept(
      net::make_strand(ioc_),
      beast::bind_front_handler(&Listener::on_accept, shared_from_this()));
}

void Listener::on_accept(beast::error_code ec, tcp::socket socket) {
  if (ec) {
    failServer(ec, "accept");
  } else {
    std::make_shared<ServerSession>(std::move(socket), doc_root_)->run();
  }

  do_accept();
}
