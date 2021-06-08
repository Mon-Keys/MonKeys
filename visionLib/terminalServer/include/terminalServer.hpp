// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_TERMINALREQUEST_HPP_
#define VISIONLIB_INCLUDE_TERMINALREQUEST_HPP_

#include <algorithm>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/config.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace beast = boost::beast;  // from <boost/beast.hpp>
namespace http = beast::http;    // from <boost/beast/http.hpp>
namespace net = boost::asio;     // from <boost/asio.hpp>
namespace property_tree = boost::property_tree;
using tcp = boost::asio::ip::tcp;  // from <boost/asio/ip/tcp.hpp>

class terminalServer {
 public:
  void waitRequest();
  void waitConnection();
  void reply();
};

beast::string_view mime_type_terminal(beast::string_view path);

std::string path_cat_terminal(beast::string_view base, beast::string_view path);

template <class Body, class Allocator, class Send>
void handle_request_terminal(
    beast::string_view doc_root,
    http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send);


void failTerminalServer(beast::error_code ec, char const* what);

class TerminalServerSession
    : public std::enable_shared_from_this<TerminalServerSession> {
  struct send_lambda {
    TerminalServerSession& self_;

    explicit send_lambda(TerminalServerSession& self) : self_(self) {}

    template <bool isRequest, class Body, class Fields>
    void operator()(http::message<isRequest, Body, Fields>&& msg) const;
  };

  beast::tcp_stream stream_;
  beast::flat_buffer buffer_;
  std::shared_ptr<std::string const> doc_root_;
  http::request<http::string_body> req_;
  std::shared_ptr<void> res_;
  send_lambda lambda_;

 public:
  TerminalServerSession(tcp::socket&& socket,
                        std::shared_ptr<std::string const> const& doc_root)
      : stream_(std::move(socket)), doc_root_(doc_root), lambda_(*this) {}

  void run();

  void do_read();

  void on_read(beast::error_code ec, std::size_t bytes_transferred);

  void on_write(bool close, beast::error_code ec,
                std::size_t bytes_transferred);

  void do_close();
};


class TerminalListener : public std::enable_shared_from_this<TerminalListener> {
  net::io_context& ioc_;
  tcp::acceptor acceptor_;
  std::shared_ptr<std::string const> doc_root_;

 public:
  TerminalListener(net::io_context& ioc, tcp::endpoint endpoint,
                   std::shared_ptr<std::string const> const& doc_root)
      : ioc_(ioc), acceptor_(net::make_strand(ioc)), doc_root_(doc_root) {
    beast::error_code ec;

    acceptor_.open(endpoint.protocol(), ec);
    if (ec) {
      failTerminalServer(ec, "open");
      return;
    }

    acceptor_.set_option(net::socket_base::reuse_address(true), ec);
    if (ec) {
      failTerminalServer(ec, "set_option");
      return;
    }

    acceptor_.bind(endpoint, ec);
    if (ec) {
      failTerminalServer(ec, "bind");
      return;
    }

    acceptor_.listen(net::socket_base::max_listen_connections, ec);
    if (ec) {
      failTerminalServer(ec, "listen");
      return;
    }
  }

  void run();

 private:
  void do_accept();

  void on_accept(beast::error_code ec, tcp::socket socket);
};

#endif  // VISIONLIB_INCLUDE_TERMINALREQUEST_HPP_
