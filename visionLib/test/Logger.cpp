// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "Logger.hpp"

#include "gtest/gtest.h"


TEST(openLogFile, correctFile) {
  Logger ErrorLogger(LOG_ERROR_FATAL);
  std::string FilePath = "../log.log";
  LogFile lf(FilePath);
  ErrorLogger.OpenLog(lf);
  EXPECT_TRUE(lf.isOpen());
  lf.CloseLog();
}

TEST(openLogFile, wrongFile) {
  Logger ErrorLogger(LOG_ERROR_FATAL);
  std::string FilePath = "brokenpath";
  LogFile lf(FilePath);
  ErrorLogger.OpenLog(lf);
  EXPECT_FALSE(lf.isOpen());
  lf.CloseLog();
}

TEST(closeLogFile, correctClose){
  Logger ErrorLogger(LOG_ERROR_FATAL);
  std::string FilePath = "brokenpath";
  LogFile lf(FilePath);
  ErrorLogger.OpenLog(lf);
  EXPECT_TRUE(lf.isOpen());
  ErrorLogger.CloseLog(lf);
  EXPECT_FALSE(lf.isOpen());
}
