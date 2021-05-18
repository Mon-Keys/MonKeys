// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_TERMINAL_HPP_
#define VISIONLIB_INCLUDE_TERMINAL_HPP_

#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Verification.hpp"

namespace beast = boost::beast;    // from <boost/beast.hpp>
namespace http = beast::http;      // from <boost/beast/http.hpp>
namespace net = boost::asio;       // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;  // from <boost/asio/ip/tcp.hpp>
namespace property_tree = boost::property_tree;

class Terminal : public Verification {
 public:
  class TempCode {
   private:
    std::string tempCode;
    bool isValid;

   public:
    TempCode();
    explicit TempCode(std::string _tempCode, bool isValid = false);
    ~TempCode();
    TempCode(const TempCode&) = delete;
    TempCode(TempCode&&) = default;
    TempCode& operator=(const TempCode&) = delete;
    TempCode& operator=(TempCode&&) = delete;
    void setTempCode(std::string readTempCode);
    bool isTempCodeValid();
    std::string getTempCode();
  };

  Terminal(TempCode _tempCode, std::string _ID, bool isConnected = false);
  Terminal();
  ~Terminal();
  Terminal(const Terminal&) = delete;
  Terminal(Terminal&&) = delete;
  Terminal& operator=(const Terminal&) = delete;
  Terminal& operator=(Terminal&&) = delete;
  void open();
  std::string readTimeCode();
  bool getIsConnected();
  void establishConnection(const char* url);
  void checkTempCodeValidity();
  void setCompanyID(std::string companyID);
  std::string getCompanyID();
  TempCode getCurrentTempCode();

 private:
  void serverRequest();
  std::string ID;
  TempCode currentTempCode;
  bool isConnected;
  bool isVerification;
};

//------------------------------------------------------------------------------

bool exists(const std::string& name);

// Report a failure
void failTerminal(beast::error_code ec, char const* what);

template <class Body, class Allocator, class Send>
void sendTerminalRequest(
    beast::error_code ec,
    http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send);

// Performs an HTTP GET and prints the response
class TerminalSession : public std::enable_shared_from_this<TerminalSession> {
  struct send_lambda {
    TerminalSession& self_;

    explicit send_lambda(TerminalSession& self) : self_(self) {}

    template <bool isRequest, class Body, class Fields>
    void operator()(http::message<isRequest, Body, Fields>&& msg) const;
  };

  tcp::resolver resolver_;
  beast::tcp_stream stream_;
  beast::flat_buffer buffer_;  // (Must persist between reads)
  http::request<http::file_body> req_;
  http::response<http::string_body> res_;
  std::shared_ptr<void> reqsp_;
  send_lambda lambda_;

 public:
  // Objects are constructed with a strand to
  // ensure that handlers do not execute concurrently.
  explicit TerminalSession(net::io_context& ioc)
      : resolver_(net::make_strand(ioc)),
        stream_(net::make_strand(ioc)),
        lambda_(*this) {}

  // Start the asynchronous operation
  void run(char const* host, char const* port, std::string target, int version);

  void on_resolve(beast::error_code ec, tcp::resolver::results_type results);

  void on_connect(beast::error_code ec,
                  tcp::resolver::results_type::endpoint_type);

  void on_write(bool close, beast::error_code ec,
                std::size_t bytes_transferred);

  void do_read();

  void on_read(beast::error_code ec, std::size_t bytes_transferred);
};

#endif  // VISIONLIB_INCLUDE_TERMINAL_HPP_
