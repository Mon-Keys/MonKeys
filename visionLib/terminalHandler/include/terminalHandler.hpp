// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_TERMINALSERVER_HPP_
#define VISIONLIB_INCLUDE_TERMINALSERVER_HPP_

#include <string>

#include "database.hpp"

class TerminalHandler {
 public:
  TerminalHandler() : _Cldb(), _Codb(), _Passdb(), _Passagedb(){};

  std::string compareTimeCode(const std::string& timeCode,
                              const uint64_t& CompanyID);

 private:
  ClientDataBase _Cldb;
  CompanyDataBase _Codb;
  PassDataBase _Passdb;
  PassageDataBase _Passagedb;
};

#endif  // VISIONLIB_INCLUDE_TERMINALSERVER_HPP_
