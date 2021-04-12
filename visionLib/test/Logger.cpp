#include "gtest/gtest.h"

#include "../include/Logger.hpp";

TEST(openLogFile, correctFile){
    Logger ErrorLogger(LOG_ERROR_FATAL);
    std::string FilePath = "../log.log";
    LogFile lf(FilePath);
    lf.OpenLog()
    ErrorLogger.write
    lf.CloseLog()
}