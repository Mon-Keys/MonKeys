// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_CLIENTREQUEST_HPP_
#define VISIONLIB_INCLUDE_CLIENTREQUEST_HPP_

class ClientRequest {
 public:
  ClientRequest();
  ~ClientRequest();

  ClientRequest(const ClientRequest&) = delete;
  ClientRequest(ClientRequest&&) = delete;

  ClientRequest& operator=(const ClientRequest&) = delete;
  ClientRequest& operator=(ClientRequest&&) = delete;

 private:
  void initServer();
  void initLogger();
  void setLoggerLevel();
  void waitConnection();
  void waitRequest();
  void runHandler();
  void reply();
};

#endif  // VISIONLIB_INCLUDE_CLIENTREQUEST_HPP_
