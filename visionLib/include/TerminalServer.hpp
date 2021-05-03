<<<<<<< HEAD
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

class TerminalServer {
 public:
  bool generateTimeCode(uint64_t PassID);
  bool compareTimeCode(std::string firstTimeCode, std::string secondTimeCode);

 private:
};

#endif  // VISIONLIB_INCLUDE_TERMINALSERVER_HPP_
=======
>>>>>>> 604e7b1a12f46225ef2f1bb28b9c47f50695f080
