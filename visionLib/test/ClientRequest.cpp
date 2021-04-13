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

class MockClientServer : public ClientServer {
 public:
  MOCK_METHOD1(getClientDataFromDB, void(uint64_t ID));
  MOCK_METHOD1(getPassDataFromDB, void(uint64_t PassID));
  MOCK_METHOD1(getCompanyDataFromDB, void(uint64_t CompanyID));
  MOCK_METHOD2(logInClient, void(std::string Login, std::string Password));
  MOCK_METHOD1(logOutClient, void(uint64_t ClientID));
  MOCK_METHOD2(registerClient, void(std::string Login, std::string Password));
  MOCK_METHOD1(getTimeCode, void(uint64_t PassID));
};

TEST(MockClientServer, RequestHandlerTest) {
  MockClientServer clientServer;

  EXPECT_CALL(clientServer, getClientDataFromDB).Times(testing::AtLeast(1));
}
