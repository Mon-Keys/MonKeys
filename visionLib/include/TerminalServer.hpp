// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_TERMINALSERVER_HPP_
#define VISIONLIB_INCLUDE_TERMINALSERVER_HPP_

class TerminalServer {
 public:
  void getClientDataFromDB();
  void getPassDataFromDB();
  void getCompanyDataFromDB();
  void generateTimeCode();
  void compareTimeCode();

 private:
};

#endif  // VISIONLIB_INCLUDE_TERMINALSERVER_HPP_
