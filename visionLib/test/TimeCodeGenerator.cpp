<<<<<<< HEAD
// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "TimeCodeGenerator.hpp"

#include "gtest/gtest.h"

TEST(TimeCodeGeneratorTest, correct_generate_on_one_time_segment) {
  uint64_t PassID = 1;
  uint16_t timeInterval = 10000;
  uint64_t timeStamp = 1618494933;
  uint64_t companyID = 1;
  std::string userKey = "JBSWY3DPEHPK3PXP";
  TimeCodeGenerator codegen(userKey, PassID, companyID, timeInterval,
                            timeStamp);
  std::string generatedCode = codegen.generateTimeCode();
  std::string precalculatedCode = "000100115247474";
  ASSERT_EQ(generatedCode, precalculatedCode);
}

TEST(TimeCodeGeneratorTest, correct_generate_on_one_time_segment2) {
  uint64_t PassID = 4096;
  uint16_t timeInterval = 100;
  uint64_t timeStamp = 1618495933;
  uint64_t companyID = 4096;
  std::string userKey =
      "asddsdsdsdsddsdsfvdsfvsadsadasowkqefoiwefjwe";  // NOLINT
  TimeCodeGenerator codegen(userKey, PassID, companyID, timeInterval,
                            timeStamp);
  std::string generatedCode = codegen.generateTimeCode();
  std::string precalculatedCode = "010010012249111";
  ASSERT_EQ(generatedCode, precalculatedCode);
}

TEST(validCheck, wrongSizeBig) {
  TimeCode code("010010012sadsadgsd249111dsadsadsa");
  EXPECT_FALSE(code.isValid());
}

TEST(validCheck, wrongSizeSmall) {
  TimeCode code("01");
  EXPECT_FALSE(code.isValid());
}

TEST(validCheck, wrongSymbolsrightSize) {
  TimeCode code("ывавыащшаоцушщо");
  EXPECT_FALSE(code.isValid());
}

TEST(validCheck, correct) {
  TimeCode code("0100100ABABABAB");
  EXPECT_TRUE(code.isValid());
}

TEST(getCompanyID, correctCode) {
  TimeCode code("010010012249111");
  uint64_t companyID = 4096;
  EXPECT_TRUE(code.isValid());
  ASSERT_EQ(companyID, code.getCompanyID());
}

TEST(getPassID, correctCode) {
  TimeCode code("010010012249111");
  uint64_t PassID = 4096;
  EXPECT_TRUE(code.isValid());
  ASSERT_EQ(PassID, code.getPassID());
}

TEST(getTimePart, correctCode) {
  TimeCode code("0100100ABABABAB");
  std::string timePart = "ABABABAB";
  EXPECT_TRUE(code.isValid());
  ASSERT_EQ(timePart, code.getTimePart());
}
=======
>>>>>>> 604e7b1a12f46225ef2f1bb28b9c47f50695f080
