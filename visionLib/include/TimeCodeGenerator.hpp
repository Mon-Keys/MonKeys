// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_TIMECODEGENERATOR_HPP_
#define VISIONLIB_INCLUDE_TIMECODEGENERATOR_HPP_

#include <iostream>
#include <string>

class TimeCodeGenerator {
 private:
  std::string privateKey;
  uint64_t PassID;
  uint64_t timeStamp;
  uint16_t timeInterval;

  // startTime --- UNIX0

  std::string getHashedOTP();
  uint64_t getTParameter();
  void updateTime();

 public:
  TimeCodeGenerator(std::string privateKey, uint64_t PassID,
                    uint16_t timeInterval);
  std::string generateTimeCode();
  TimeCodeGenerator();
  ~TimeCodeGenerator();
  TimeCodeGenerator(const TimeCodeGenerator&) = delete;
  TimeCodeGenerator(TimeCodeGenerator&&) = default;
};

#endif  // VISIONLIB_INCLUDE_TIMECODEGENERATOR_HPP_
