// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_VERIFICATION_HPP_
#define VISIONLIB_INCLUDE_VERIFICATION_HPP_

class Verification {
 public:
  virtual void open() = 0;
  virtual void establishConnection(const char *url) = 0;
};

#endif  // VISIONLIB_INCLUDE_VERIFICATION_HPP_
