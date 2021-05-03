<<<<<<< HEAD
// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/
#include "TerminalRequest.hpp"

#include "TerminalServer.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class MockTerminalServer : public TerminalServer {
 public:
  MOCK_METHOD0(compareTimeCode, void());
  MOCK_METHOD0(generateTimeCode, void());
};

TEST(MockClientServer, RequestTerminalHandlerTest) {
  MockTerminalServer terminalServer;
  EXPECT_CALL(terminalServer, compareTimeCode).Times(testing::AtLeast(1));
}
=======
>>>>>>> 604e7b1a12f46225ef2f1bb28b9c47f50695f080
