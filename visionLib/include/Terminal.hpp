// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_TERMINAL_HPP_
#define VISIONLIB_INCLUDE_TERMINAL_HPP_

#include <string>

class Terminal {
 public:
  void open();
  void readTimeCode();

 private:
  void serverRequest();
  void establishConnection();

  uint64_t ID;
};

#endif  // VISIONLIB_INCLUDE_TERMINAL_HPP_
