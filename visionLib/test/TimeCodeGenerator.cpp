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
  uint16_t timeInterval = 30;
  uint64_t companyID = 1;
  uint64_t floor = (std::time(0) / timeInterval);
  std::string userKey = "JBSWY3DPEHPK3PXP";
  TimeCodeGenerator codegen(userKey, PassID, companyID, timeInterval);
  std::string generatedCode = codegen.generateTimeCode();
  sleep(2);
  if ((std::time(0) / timeInterval) == floor) {
    ASSERT_EQ(generatedCode, codegen.generateTimeCode());
  } else {
    ASSERT_NE(generatedCode, codegen.generateTimeCode());
  }
}


TEST(getCompanyID, easyInput) {
  uint64_t PassID = 1;
  uint16_t timeInterval = 30;
  uint64_t companyID = 1;
  uint64_t floor = (std::time(0) / timeInterval);
  std::string userKey = "JBSWY3DPEHPK3PXP";
  TimeCodeGenerator codegen(userKey, PassID, companyID, timeInterval);
  std::string generatedCode = codegen.generateTimeCode();
  TimeCode tc(generatedCode);
  ASSERT_EQ(tc.getCompanyID(), companyID);
}

TEST(getPassID, easyInput) {
  uint64_t PassID = 1;
  uint16_t timeInterval = 30;
  uint64_t companyID = 1;
  uint64_t floor = (std::time(0) / timeInterval);
  std::string userKey = "JBSWY3DPEHPK3PXP";
  TimeCodeGenerator codegen(userKey, PassID, companyID, timeInterval);
  std::string generatedCode = codegen.generateTimeCode();
  TimeCode tc(generatedCode);
  ASSERT_EQ(tc.getPassID(), PassID);
}

TEST(getPassID, completeCheck) {
  uint64_t PassID = 1544716917;
  uint16_t timeInterval = 30;
  uint64_t companyID = 13303233;
  uint64_t floor = (std::time(0) / timeInterval);
  std::string userKey = "JBSWY3DPEHPK3PXP";
  TimeCodeGenerator codegen(userKey, PassID, companyID, timeInterval);
  std::string generatedCode = codegen.generateTimeCode();
  TimeCode tc(generatedCode);
  ASSERT_EQ(tc.getPassID(), PassID);
}

TEST(getCompanyID, completeCheck) {
  uint64_t PassID = 1544716917;
  uint16_t timeInterval = 30;
  uint64_t companyID = 13303233;
  uint64_t floor = (std::time(0) / timeInterval);
  std::string userKey = "JBSWY3DPEHPK3PXP";
  TimeCodeGenerator codegen(userKey, PassID, companyID, timeInterval);
  std::string generatedCode = codegen.generateTimeCode();
  TimeCode tc(generatedCode);
  ASSERT_EQ(tc.getCompanyID(), companyID);
}



TEST(validCheck, wrongSizeBig) {
  TimeCode code("010010012sadsadgsd249111dsadsadsa");
  EXPECT_FALSE(code.isValid());
}

TEST(validCheck, wrongSizeSmall) {
  TimeCode code("01");
  EXPECT_FALSE(code.isValid());
}

TEST(validCheck, rightSize) {
  TimeCode code("1004142038041431102930");
  EXPECT_TRUE(code.isValid());
}



