// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_WEBAPPLICATIONCLIENT_HPP_
#define VISIONLIB_INCLUDE_WEBAPPLICATIONCLIENT_HPP_

#include <string>

class IWebApplicationClient {
 public:
  virtual void logIn() = 0;
  virtual void logOut() = 0;
  virtual void registerClient() = 0;
  virtual void requestPasses() = 0;
  virtual std::string getTempPass(uint64_t passID) = 0;

  virtual void establishConnection(const char *url) = 0;
  virtual void breakConection() = 0;
};

#endif  // VISIONLIB_INCLUDE_WEBAPPLICATIONCLIENT_HPP_
