// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_TIMECODE_INCLUDE_TIMECODEGENERATOR_HPP_
#define VISIONLIB_TIMECODE_INCLUDE_TIMECODEGENERATOR_HPP_

#include <bitset>
#include <boost/format.hpp>
#include <boost/uuid/detail/sha1.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

class TimeCodeGenerator {
 private:
  std::string _privateKey;
  uint64_t _PassID;
  uint16_t _timeInterval;
  uint64_t _CompanyID;

  // startTime --- UNIX0

  std::string getHashedOTP();
  uint64_t getTParameter();
  void updateTime();
  uint64_t countFloor();
  std::string getSHA1(const std::string& message);
  uint8_t convertHexCharToUINT(char ch);
  std::bitset<88> convertHexTokenToBitset(std::string hexToken);
  std::bitset<88> tableEncoding(std::bitset<88> binToken);
  std::string binTokenToHex(std::string);

 public:
  TimeCodeGenerator(std::string privateKey, uint64_t PassID, uint64_t CompanyID,
                    uint16_t timeInterval);
  std::string generateTimeCode();
  std::vector<std::string> generateTimeCodesAhead(uint8_t timecodesAmount);
  TimeCodeGenerator();
  ~TimeCodeGenerator();
  TimeCodeGenerator(const TimeCodeGenerator&) = delete;
  TimeCodeGenerator(TimeCodeGenerator&&) = default;
};

class TimeCode {
 private:
  std::bitset<88> timecodeDecoded;
  bool valid;
  uint8_t convertHexCharToUINT(char ch);
  std::bitset<88> decodeTable(std::bitset<88> binToken);
  std::bitset<88> convertHexTokenToBitset(std::string hexToken);

 public:
  bool isValid();
  explicit TimeCode(std::string timecodeString);
  ~TimeCode();
  uint64_t getCompanyID();
  uint64_t getPassID();
};

#endif  // VISIONLIB_TIMECODE_INCLUDE_TIMECODEGENERATOR_HPP_
