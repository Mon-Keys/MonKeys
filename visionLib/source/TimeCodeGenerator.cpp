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
