// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "terminalClient.hpp"

TEST(TestTerminal, correct_tempcode_lenght) {
  Terminal terminal;
  std::string currentTempCode;
  currentTempCode = terminal.readTimeCode();
  uint8_t currentLength = currentTempCode.length();
  uint8_t expectedLength = 15;
  EXPECT_EQ(currentLength, expectedLength);
}

TEST(TestTerminal, correct_getiing_temp_code) {
  Terminal terminal;
  Terminal::TempCode tempCode;
  std::string currentTempCode;
  currentTempCode = "DFW1216LKWLKW2";
  tempCode.setTempCode(currentTempCode);
  std::string realTempCode;
  realTempCode = tempCode.getTempCode();
  EXPECT_EQ(realTempCode, currentTempCode);
}

TEST(TestClient, correct_connecton_establishing) {
  Terminal terminal;
  const char *url = "http://google.com";
  terminal.establishConnection(url);
  EXPECT_TRUE(terminal.getIsConnected());
}

TEST(TestClient, correct_set_company_id) {
  Terminal terminal;
  std::string _companyID = "Y1A";
  terminal.setCompanyID(_companyID);
  EXPECT_EQ("Y1A", terminal.getCompanyID());
}

class MockTempCode : public Terminal::TempCode {
 public:
  MOCK_METHOD0(getCurrentTempCode, std::string());
  MOCK_METHOD0(isTempCodeValid, bool());
};

TEST(TestTerminal, valid_temp_code) {
  Terminal terminal;
  MockTempCode tempCode;
  std::string currentTempCode;
  std::string companyID;
  companyID = "261";
  terminal.setCompanyID(companyID);
  currentTempCode = "DFW1216LKWLKW2";
  tempCode.setTempCode(currentTempCode);
  bool validity = true;
  terminal.checkTempCodeValidity();
  validity = tempCode.isTempCodeValid();
  EXPECT_TRUE(validity);
}

TEST(TestTerminal, invalid_temp_code) {
  Terminal terminal;
  MockTempCode tempCode;
  std::string currentTempCode;
  std::string companyID;
  companyID = "211";
  terminal.setCompanyID(companyID);
  currentTempCode = "DFW1216LKWLKW2";
  tempCode.setTempCode(currentTempCode);
  bool validity = false;
  terminal.checkTempCodeValidity();
  validity = tempCode.isTempCodeValid();
  EXPECT_FALSE(validity);
}
