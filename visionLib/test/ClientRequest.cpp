// Copyright 2021 MonKeys

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../include/ClientRequest.hpp"
#include "../include/ClientServer.hpp"

class MockClientServer : public ClientServer {
 public:
    MOCK_METHOD1(getClientDataFromDB, void(long ID));
    MOCK_METHOD1(getPassDataFromDB, void(long PassID));
    MOCK_METHOD1(getCompanyDataFromDB, void(long CompanyID));
    MOCK_METHOD2(logInClient, void(std::string Login, std::string Password));
    MOCK_METHOD1(logOutClient, void(long ClientID));
    MOCK_METHOD2(registerClient, void(std::string Login, std::string Password));
    MOCK_METHOD1(getTimeCode, void(long PassID));
}

TEST(MockClientServer, RequestHandlerTest) {
    MockClientServer clientServer;
    
    EXPECT_CALL(clientServer, getClientDataFromDB).Times(testing::AtLeast(1));
}
