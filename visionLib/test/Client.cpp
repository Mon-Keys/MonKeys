// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "Client.hpp"

#include "gtest/gtest.h"

TEST(TestClient, correct_log_in) {
  Client client;
  const char *url = "http://mail.ru";
  client.establishConnection(url);
  client.logIn();
  EXPECT_TRUE(client.getIsLogIn());
  client.breakConection();
}

TEST(TestClient, unauthorized_client) {
  Client client;
  const char *url = "http://mail.ru";
  client.establishConnection(url);
  EXPECT_FALSE(client.getIsLogIn());
  client.breakConection();
}

TEST(TestClient, correct_log_out) {
  Client client;
  const char *url = "http://mail.ru";
  client.establishConnection(url);
  client.logIn();
  client.logOut();
  EXPECT_FALSE(client.getIsLogIn());
  client.breakConection();
}

TEST(TestClient, correct_registration) {
  Client client;
  const char *url = "http://mail.ru";
  client.establishConnection(url);
  client.registerClient();
  EXPECT_TRUE(client.getIsLogIn());
  client.breakConection();
}

/*
TEST(TestClient, correct_getting_temp_pass) {
  Client client;
  const char *url = "htttp://mail.ru";
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
  companyNames[1] = "steam";
  companyNames[2] = "lol";
  companyNames[3] = "mda";
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
  client.breakConection();
}
*/

TEST(TestClient, correct_connecton_establishing) {
  Client client;
  const char *url = "http://mail.ru";
  client.establishConnection(url);
  EXPECT_TRUE(client.getIsConnected());
  client.breakConection();
}
