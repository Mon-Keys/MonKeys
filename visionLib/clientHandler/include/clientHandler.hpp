// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_CLIENTHANDLER_HPP_
#define VISIONLIB_INCLUDE_CLIENTHANDLER_HPP_

#include <ctime>
#include <string>

#include "database.hpp"

class clientHandler {
 public:
  clientHandler() : _Cldb(), _Codb(), _Passdb(), _Passagedb(){};

  std::string logInClient(const std::string& Login,
                          const std::string& Password);
  std::string logOutClient(uint64_t ClientID);
  std::string registerClient(const std::string& Login, const std::string& Email,
                             const std::string& Password);
  std::string getTimeCode(const std::string& Login,
                          const std::string& Password);
  std::string logInAdmin(const std::string& CompanyName,
                         const std::string& LecenseKey);
  std::string addCleintsPass(const std::string& Login,
                            const std::string& Name);
  std::string logOutAdmin();

 private:
  ClientDataBase _Cldb;
  CompanyDataBase _Codb;
  PassDataBase _Passdb;
  PassageDataBase _Passagedb;
};

#endif  // VISIONLIB_INCLUDE_CLIENTHANDLER_HPP_
