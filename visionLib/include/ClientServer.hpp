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
  void getClientDataFromDB(uint64_t ID);
  void getPassDataFromDB(uint64_t PassID);
  void getCompanyDataFromDB(uint64_t CompanyID);
  void logInClient(std::string Login, std::string Password);
  void logOutClient(uint64_t ClientID);
  void registerClient(std::string Login, std::string Password);
  void getTimeCode(uint64_t PassID);

 private:
};

#endif  // VISIONLIB_INCLUDE_CLIENTSERVER_HPP_
