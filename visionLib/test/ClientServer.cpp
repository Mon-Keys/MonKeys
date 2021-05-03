<<<<<<< HEAD
// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "../include/ClientServer.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;

class MockClientServer : public ClientServer {
 public:
  MOCK_METHOD2(logInClient, bool(std::string Login, std::string Password));
  MOCK_METHOD1(logOutClient, bool(uint64_t ClientID));
  MOCK_METHOD2(registerClient, bool(std::string Login, std::string Password));
  MOCK_METHOD1(getTimeCode, std::string(uint64_t PassID));
};

TEST(MOCKClientServer, logInTest) {
  MockClientServer mcs;

  ON_CALL(mcs, logInClient(_, _)).WillByDefault(Return(true));

  bool ex = mcs.logInClient("dasd", "dasd");
  EXPECT_EQ(ex, 1);
}

TEST(MOCKClientServer, logOutTest) {
  MockClientServer mcs;

  ON_CALL(mcs, logOutClient(_)).WillByDefault(Return(true));

  bool ex = mcs.logOutClient(1);
  EXPECT_EQ(ex, 1);
}

TEST(MOCKClientServer, registerTest) {
  MockClientServer mcs;

  ON_CALL(mcs, registerClient(_, _)).WillByDefault(Return(true));

  bool ex = mcs.registerClient("dasd", "dasd");
  EXPECT_EQ(ex, 1);
}

TEST(MOCKClientServer, getTimeCodeTest) {
  MockClientServer mcs;

  ON_CALL(mcs, getTimeCode(_)).WillByDefault(Return("abcd"));

  std::string ex = mcs.getTimeCode(1);
  // EXPECT_STREQ(ex, "abcd");
}
=======
>>>>>>> 604e7b1a12f46225ef2f1bb28b9c47f50695f080
