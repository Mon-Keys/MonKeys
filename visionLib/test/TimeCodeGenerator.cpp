// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "TimeCodeGenerator.hpp"

#include "gtest/gtest.h"


/*
TEST(TimeCodeGeneratorTest, correct_generate_on_one_time_segment) {
  uint64_t PassID = 1;
  uint16_t timeInterval = 30;
  std::string userKey = "dsadsadsadassadejigfwjgwiue";

  TimeCodeGenerator codegen(userKey, PassID, timeInterval);

  std::string generatedCode = codegen.generateTimeCode();

  std::string precalculatedCode = "NDS0FESKOKOG";

  ASSERT_EQ(generatedCode, precalculatedCode);
}

TEST(TimeCodeGeneratorTest, zeroTimeInterval) {
  uint64_t PassID = 1;
  uint16_t timeInterval = 0;
  std::string userKey = "dsadsadsadassadejigfwjgwiue";

  TimeCodeGenerator codegen(userKey, PassID, timeInterval);

  std::string generatedCode = codegen.generateTimeCode();

  EXPECT_TRUE(generatedCode.empty());
}
*/
