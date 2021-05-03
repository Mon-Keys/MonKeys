<<<<<<< HEAD
// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "ClientRequest.hpp"

#include "ClientServer.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::AtLeast;
using ::testing::Return;

class MockClientServer : public ClientServer {
 public:
  MOCK_METHOD2(logInClient, void(std::string Login, std::string Password));
  MOCK_METHOD1(logOutClient, void(uint64_t ClientID));
  MOCK_METHOD2(registerClient, void(std::string Login, std::string Password));
  MOCK_METHOD1(getTimeCode, void(uint64_t PassID));
};

TEST(MockClientServer, RequestHandlerTest) {
  ASSERT_TRUE(true);

  MockClientServer clientServer;
  EXPECT_CALL(clientServer, logInClient).Times(testing::AtLeast(1));
}
=======
>>>>>>> 604e7b1a12f46225ef2f1bb28b9c47f50695f080
