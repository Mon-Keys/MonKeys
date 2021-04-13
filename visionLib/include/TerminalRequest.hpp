// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_TERMINALREQUEST_HPP_
#define VISIONLIB_INCLUDE_TERMINALREQUEST_HPP_

class TerminalServer {
 public:
  void waitRequest();
  void waitConnection();
  void reply();
};

#endif  // VISIONLIB_INCLUDE_TERMINALREQUEST_HPP_
