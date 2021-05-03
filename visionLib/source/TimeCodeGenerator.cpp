<<<<<<< HEAD
// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "../include/TimeCodeGenerator.hpp"

#include <iostream>

std::string TimeCodeGenerator::generateTimeCode() {
  std::cout << "hello" << std::endl;
  return "hello";
}

TimeCodeGenerator::TimeCodeGenerator() {}

TimeCodeGenerator::~TimeCodeGenerator() {}

std::string TimeCodeGenerator::getHashedOTP() { return ""; }

void TimeCodeGenerator::updateTime() {}

uint64_t TimeCodeGenerator::getTParameter() { return 1; }

// cppcheck-suppress uninitMemberVar
TimeCodeGenerator::TimeCodeGenerator(std::string privateKey, uint64_t PassID,
                                     uint64_t CompanyID, uint16_t timeInterval,
                                     uint64_t timeStamp) {}

// cppcheck-suppress uninitMemberVar
TimeCode::TimeCode(std::string timecodeString) {}

TimeCode::~TimeCode() {}

uint64_t TimeCode::decodeFrom64(std::string toDecode) {}

uint64_t TimeCode::getCompanyID() {}

uint64_t TimeCode::getPassID() {}

bool TimeCode::isValid() {}

std::string TimeCode::getTimePart() {}
=======
>>>>>>> 604e7b1a12f46225ef2f1bb28b9c47f50695f080
