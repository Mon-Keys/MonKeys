// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/
#ifndef VISIONLIB_INCLUDE_clientServer_HPP_
#define VISIONLIB_INCLUDE_clientServer_HPP_

class clientServer {
 public:
  clientServer();
  ~clientServer();

  clientServer(const clientServer&) = delete;
  clientServer(clientServer&&) = delete;

  clientServer& operator=(const clientServer&) = delete;
  clientServer& operator=(clientServer&&) = delete;

 private:
  void initServer();
  void initLogger();
  void setLoggerLevel();
  void waitConnection();
  void waitRequest();
  void runHandler();
  void reply();
};

#endif  // VISIONLIB_INCLUDE_clientServer_HPP_
