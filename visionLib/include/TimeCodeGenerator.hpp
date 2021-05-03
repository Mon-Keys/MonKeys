<<<<<<< HEAD
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
  TimeCodeGenerator(std::string privateKey, uint64_t PassID, uint64_t CompanyID,
                    uint16_t timeInterval, uint64_t timeStamp);
  std::string generateTimeCode();
  TimeCodeGenerator();
  ~TimeCodeGenerator();
  TimeCodeGenerator(const TimeCodeGenerator&) = delete;
  TimeCodeGenerator(TimeCodeGenerator&&) = default;
};

class TimeCode {
 private:
  uint64_t CompanyID;
  uint64_t PassID;
  std::string timePart;
  uint64_t decodeFrom64(std::string toDecode);
  bool valid;

 public:
  bool isValid();
  explicit TimeCode(std::string timecodeString);
  ~TimeCode();
  uint64_t getCompanyID();
  uint64_t getPassID();
  std::string getTimePart();
};

#endif  // VISIONLIB_INCLUDE_TIMECODEGENERATOR_HPP_
=======
>>>>>>> 604e7b1a12f46225ef2f1bb28b9c47f50695f080
