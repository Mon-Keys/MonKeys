// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "Client.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::AtLeast;
using ::testing::Return;

TEST(TestClient, correct_log_in) {
  Client client;
  const char *url = "http://mail.ru";
  client.establishConnection(url);
  client.logIn();
  EXPECT_TRUE(client.getIsLogIn());
  client.breakConnection();
}

TEST(TestClient, unauthorized_client) {
  Client client;
  const char *url = "http://mail.ru";
  client.establishConnection(url);
  EXPECT_FALSE(client.getIsLogIn());
  client.breakConnection();
}

TEST(TestClient, correct_log_out) {
  Client client;
  const char *url = "http://mail.ru";
  client.establishConnection(url);
  client.logIn();
  client.logOut();
  EXPECT_FALSE(client.getIsLogIn());
  client.breakConnection();
}

TEST(TestClient, correct_registration) {
  Client client;
  const char *url = "http://mail.ru";
  client.establishConnection(url);
  client.registerClient();
  EXPECT_TRUE(client.getIsLogIn());
  client.breakConnection();
}

TEST(TestClient, correct_getting_temp_pass) {
  Client client;
  const char *url = "http://mail.ru";
  client.establishConnection(url);
  client.logIn();
  const int numberOfPasses = 4;
  Client::Pass *currentPasses = new Client::Pass[numberOfPasses];
  std::string *privateKeys = new std::string[numberOfPasses];
  privateKeys[0] = "qwert";
  privateKeys[1] = "zxcvb";
  privateKeys[2] = "qwertyujhgfcx";
  privateKeys[3] = "vbhgfvbnm";
  std::string *companyNames = new std::string[numberOfPasses];
  companyNames[0] = "Mail.ru";
  companyNames[1] = "Steam";
  companyNames[2] = "MonKeys";
  companyNames[3] = "BMSTU";
  for (uint64_t i = 0; i < numberOfPasses; i++) {
    currentPasses[i].setID(i);
    currentPasses[i].setPrivateKey(privateKeys[i]);
    currentPasses[i].setCompanyName(companyNames[i]);
  }
  client.setPasses(currentPasses);
  std::string firstTempPass = client.getTempPass(0);
  sleep(10);
  std::string secondTempPass = client.getTempPass(0);
  EXPECT_EQ(firstTempPass, secondTempPass);
  client.breakConnection();
  delete[] currentPasses;
  delete[] privateKeys;
  delete[] companyNames;
}

TEST(TestClient, correct_connecton_establishing) {
  Client client;
  const char *url = "http://mail.ru";
  client.establishConnection(url);
  EXPECT_TRUE(client.getIsConnected());
  client.breakConnection();
}

TEST(TestClient, failed_connecton_establishing) {
  Client client;
  const char *url = "http://mail.ri";
  client.establishConnection(url);
  EXPECT_FALSE(client.getIsConnected());
  client.breakConnection();
}

TEST(TestClient, correct_setting_ID) {
  Client client;
  client.setID(42);
  EXPECT_EQ(42, client.getID());
}

TEST(TestClient, correct_setting_passes_count) {
  Client client;
  client.setPassesCount(3);
  EXPECT_EQ(3, client.getPassesCount());
}

TEST(TestClient, correct_setting_is_connected_flag) {
  Client client;
  client.setIsConnected(true);
  EXPECT_TRUE(client.getIsConnected());
}

TEST(TestClient, correct_setting_is_log_in_flag) {
  Client client;
  client.setIsLogIn(true);
  EXPECT_TRUE(client.getIsConnected());
}

class MockClientPass : public Client::Pass {
 public:
  MOCK_METHOD0(requestTempCode, std::string());
};

TEST(TestClient, correct_requesting_temp_code) {
  Client client;
  const char *url = "http://mail.ru";
  client.establishConnection(url);
  client.logIn();
  const int numberOfPasses = 4;
  MockClientPass *currentPasses = new MockClientPass[numberOfPasses];
  std::string *privateKeys = new std::string[numberOfPasses];
  privateKeys[0] = "qwert";
  privateKeys[1] = "zxcvb";
  privateKeys[2] = "qwertyujhgfcx";
  privateKeys[3] = "vbhgfvbnm";
  std::string *companyNames = new std::string[numberOfPasses];
  companyNames[0] = "Mail.ru";
  companyNames[1] = "Steam";
  companyNames[2] = "MonKeys";
  companyNames[3] = "BMSTU";
  for (uint64_t i = 0; i < numberOfPasses; i++) {
    currentPasses[i].setID(i);
    currentPasses[i].setPrivateKey(privateKeys[i]);
    currentPasses[i].setCompanyName(companyNames[i]);
  }
  client.setPasses(currentPasses);
  EXPECT_CALL(currentPasses[0], requestTempCode())
      .Times(1)
      .WillOnce(Return("qwertyujghj111"));
  std::string currentTempCode = currentPasses[0].requestTempCode();
  EXPECT_EQ("qwertyujghj111", currentTempCode);
  delete[] currentPasses;
  delete[] privateKeys;
  delete[] companyNames;
}
