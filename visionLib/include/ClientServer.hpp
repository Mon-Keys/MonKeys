// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_CLIENTSERVER_HPP_
#define VISIONLIB_INCLUDE_CLIENTSERVER_HPP_

#include <ctime>
#include <string>

class ClientServer {
 public:
  bool logInClient(std::string Login, std::string Password);
  bool logOutClient(uint64_t ClientID);
  bool registerClient(std::string Login, std::string Password);
  std::string getTimeCode(uint64_t PassID);

 private:
};

#endif  // VISIONLIB_INCLUDE_CLIENTSERVER_HPP_
