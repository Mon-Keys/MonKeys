// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "Logger.hpp"

#include "gtest/gtest.h"

#define MAX_ELEMENTS 65536

bool compareFiles(FILE* file_compared, FILE* file_checked) {
  bool diff = false;
  int N = MAX_ELEMENTS;
  char* fileBuff1 = reinterpret_cast<char*>(calloc(1, N + 1));
  char* fileBuff2 = reinterpret_cast<char*>(calloc(1, N + 1));
  size_t fileComparedRead, fileCheckedRead;

  do {
    fileComparedRead = fread(fileBuff1, 1, N, file_compared);
    fileCheckedRead = fread(fileBuff2, 1, N, file_checked);

    if (fileComparedRead != fileCheckedRead ||
        memcmp(fileBuff1, fileBuff2, fileComparedRead)) {
      diff = true;
      break;
    }
  } while (!feof(file_compared) || !feof(file_checked));

  free(fileBuff1);
  free(fileBuff2);

  return diff;
}

TEST(logFileTest, writeInfo) {
  Logger Log(LOG_INFO);
  std::string testFilePath = "testData/test1.log";
  std::string writeFilePath = "testData/testWrite.log";
  LogFile lf(writeFilePath);
  Log.WriteLog(lf, "hello");
  FILE* testFile = fopen("testData/test1.log", "w+");
  FILE* writeFile = fopen("testData/testWrite.log", "w+");
  EXPECT_TRUE(compareFiles(testFile, writeFile));
  fclose(testFile);
  fclose(writeFile);
}

TEST(logFileTest, writeErrorFatal) {
  Logger Log(LOG_ERROR_FATAL);
  std::string testFilePath = "testData/test2.log";
  std::string writeFilePath = "testData/testWrite.log";
  LogFile lf(writeFilePath);

  FILE* testFile = fopen("testData/test1.log", "w+");
  FILE* writeFile = fopen("testData/testWrite.log", "w+");
  Log.WriteLog(lf, "Hello world!");
  Log.WriteLog(lf, "Hello world!");
  Log.WriteLog(lf, "Hello world!");
  Log.WriteLog(lf, "Hello world!");

  EXPECT_TRUE(compareFiles(testFile, writeFile));
  fclose(testFile);
  fclose(writeFile);
}

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

TEST(closeLogFile, correctClose) {
  Logger ErrorLogger(LOG_ERROR_FATAL);
  std::string FilePath = "brokenpath";
  LogFile lf(FilePath);
  ErrorLogger.OpenLog(lf);
  EXPECT_TRUE(lf.isOpen());
  ErrorLogger.CloseLog(lf);
  EXPECT_FALSE(lf.isOpen());
}