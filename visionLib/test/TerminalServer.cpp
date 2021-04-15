// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "../include/TerminalServer.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;

class MockTerminalServer : public TerminalServer {
 public:
  MOCK_METHOD2(compareTimeCode,
               bool(std::string firstTimeCode, std::string secondTimeCode));
  MOCK_METHOD1(generateTimeCode, bool(uint64_t PassID));
};

TEST(MOCKTerminalServer, compareTimeCodeTest) {
  MockTerminalServer mts;

  ON_CALL(mts, compareTimeCode(_, _)).WillByDefault(Return(true));

  bool ex = mts.compareTimeCode("asf", "asf");
  EXPECT_EQ(ex, true);
}

TEST(MOCKTerminalServer, generateTimeCode) {
  MockTerminalServer mts;

  ON_CALL(mts, generateTimeCode(_)).WillByDefault(Return(true));

  bool ex = mts.generateTimeCode(1);
  EXPECT_EQ(ex, true);
}
