// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "httpServer.hpp"

#include "clientHandler.hpp"

// Return a reasonable mime type based on the extension of a file.
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

// Append an HTTP rel-path to a local filesystem path.
// The returned path is normalized for the platform.
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

// This function produces an HTTP response for the given
// request. The type of the response object depends on the
// contents of the request, so the interface requires the
// caller to pass a generic lambda for receiving the response.
template <class Body, class Allocator, class Send>
void handle_request(beast::string_view doc_root,
                    http::request<Body, http::basic_fields<Allocator>>&& req,
                    Send&& send) {

    if (req.method() == http::verb::options) {
      std::cout << "jops" << std::endl;
      http::response<http::empty_body> res{http::status::no_content, req.version()};
      res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
      res.keep_alive(req.keep_alive());
      res.set(http::field::access_control_allow_origin, "http://localhost:3000");
      res.set(http::field::access_control_allow_methods, "POST");
      res.set(http::field::access_control_allow_headers, "Content-Type");
      return send(std::move(res));
  }
  std::cout << "still here" << std::endl;
  // Returns a bad request response
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

  // Returns a not found response
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

  // Returns a server error response
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

  // Make sure we can handle the method
  if (req.method() != http::verb::post && req.method() != http::verb::head &&
      req.method()!= http::verb::options)
    return send(bad_request("Unknown HTTP-method"));

  // Request path must be absolute and not contain "..".
  if (req.target().empty() || req.target()[0] != '/' ||
      req.target().find("..") != beast::string_view::npos)
    return send(bad_request("Illegal request-target"));

  // create handler
  clientHandler currentHandler;

  // Build the path to the requested file
  std::string path;
  std::string jsonName;
  //  = path_cat(doc_root, req.target());

  if (!strcmp(req.target().data(), "/registr")) {
    property_tree::ptree reqJson;
    std::stringstream jsonStream(req.body());
    property_tree::read_json(jsonStream, reqJson);
    std::string login = reqJson.get<std::string>("login");
    std::string password = reqJson.get<std::string>("password");
    std::string email = reqJson.get<std::string>("email");

    jsonName = currentHandler.registerClient(login, email, password);
  } else if (!strcmp(req.target().data(), "/auth")) {
    property_tree::ptree reqJson;
    std::stringstream jsonStream(req.body());
    
    std::cout << "still here" << std::endl;
    try {
      property_tree::read_json(jsonStream, reqJson);
      std::string login = reqJson.get<std::string>("login");
          std::string password = reqJson.get<std::string>("password");
          std::cout << "hello";
          jsonName = currentHandler.logInClient(login, password);
    }
    catch (const std::exception &exc)
      {
          std::cout << exc.what();
          std::cout << "whoop" << std::endl;
          
      }
    
  } else if (!strcmp(req.target().data(), "/timecode")) {
    property_tree::ptree reqJson;
    std::stringstream jsonStream(req.body());
    property_tree::read_json(jsonStream, reqJson);
    std::string login = reqJson.get<std::string>("login");
    std::string password = reqJson.get<std::string>("password");

    jsonName = currentHandler.getTimeCode(login, password);
  }
  path = path_cat(doc_root, "/");
  path.append(jsonName);
  // path.append("/server.json");

  // Attempt to open the file
  beast::error_code ec;
  http::file_body::value_type body;
  body.open(path.c_str(), beast::file_mode::scan, ec);

  // Handle the case where the file doesn't exist
  if (ec == beast::errc::no_such_file_or_directory) {
    return send(not_found(req.target()));
  }

  // Handle an unknown error
  if (ec) {
    return send(server_error(ec.message()));
  }

  // Cache the size since we need it after the move
  auto const size = body.size();

  std::cout << req << std::endl << req.target();
  
  
  
  
  // Respond to HEAD request
  if (req.method() == http::verb::head) {
    http::response<http::empty_body> res{http::status::ok, req.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, mime_type(path));
    res.content_length(size);
    res.keep_alive(req.keep_alive());
    res.set(http::field::access_control_allow_origin, "http://localhost:3000");
    return send(std::move(res));
  }

  // Respond to POST request
  http::response<http::file_body> res{
      std::piecewise_construct, std::make_tuple(std::move(body)),
      std::make_tuple(http::status::ok, req.version())};
  res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
  res.set(http::field::content_type, mime_type(path));
  res.content_length(size);
  res.keep_alive(req.keep_alive());
  res.set(http::field::access_control_allow_origin, "http://localhost:3000");
  std::cout << "jopa" << std::endl << std::endl;
  return send(std::move(res));
}

//------------------------------------------------------------------------------

// Report a failure
void failServer(beast::error_code ec, char const* what) {
  std::cerr << what << ": " << ec.message() << "\n";
}

template <bool isRequest, class Body, class Fields>
void ServerSession::send_lambda::operator()(
    http::message<isRequest, Body, Fields>&& msg) const {
  // The lifetime of the message has to extend
  // for the duration of the async operation so
  // we use a shared_ptr to manage it.
  auto sp =
      std::make_shared<http::message<isRequest, Body, Fields>>(std::move(msg));

  // Store a type-erased version of the shared
  // pointer in the class to keep it alive.
  self_.res_ = sp;

  // Write the response
  http::async_write(
      self_.stream_, *sp,
      beast::bind_front_handler(&ServerSession::on_write,
                                self_.shared_from_this(), sp->need_eof()));
}

// Start the asynchronous operation
void ServerSession::run() {
  // We need to be executing within a strand to perform async operations
  // on the I/O objects in this Session. Although not strictly necessary
  // for single-threaded contexts, this example code is written to be
  // thread-safe by default.
  net::dispatch(
      stream_.get_executor(),
      beast::bind_front_handler(&ServerSession::do_read, shared_from_this()));
}

void ServerSession::do_read() {
  // Make the request empty before reading,
  // otherwise the operation behavior is undefined.
  req_ = {};

  // Set the timeout.
  stream_.expires_after(std::chrono::seconds(30));

  // Read a request
  http::async_read(
      stream_, buffer_, req_,
      beast::bind_front_handler(&ServerSession::on_read, shared_from_this()));
}

void ServerSession::on_read(beast::error_code ec,
                            std::size_t bytes_transferred) {
  boost::ignore_unused(bytes_transferred);

  // This means they closed the connection
  if (ec == http::error::end_of_stream) {
    return do_close();
  }

  if (ec) {
    // std::cout << ec << "\n";
    return failServer(ec, "read");
  }

  // Send the response
  std::cout << "user connected\n";
  handle_request(*doc_root_, std::move(req_), lambda_);
}

void ServerSession::on_write(bool close, beast::error_code ec,
                             std::size_t bytes_transferred) {
  boost::ignore_unused(bytes_transferred);

  if (ec) {
    std::cout << ec << "\n";
    return failServer(ec, "write");
  }

  if (close) {
    // This means we should close the connection, usually because
    // the response indicated the "Connection: close" semantic.
    return do_close();
  }

  // We're done with the response so delete it
  res_ = nullptr;

  // Read another request
  do_read();
}

void ServerSession::do_close() {
  // Send a TCP shutdown
  beast::error_code ec;
  stream_.socket().shutdown(tcp::socket::shutdown_send, ec);

  // At this point the connection is closed gracefully
}

// Start accepting incoming connections
void Listener::run() { do_accept(); }

void Listener::do_accept() {
  // The new connection gets its own strand
  acceptor_.async_accept(
      net::make_strand(ioc_),
      beast::bind_front_handler(&Listener::on_accept, shared_from_this()));
}

void Listener::on_accept(beast::error_code ec, tcp::socket socket) {
  if (ec) {
    failServer(ec, "accept");
  } else {
    // Create the Session and run it
    std::make_shared<ServerSession>(std::move(socket), doc_root_)->run();
  }

  // Accept another connection
  do_accept();
}
