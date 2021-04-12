//
// Created by Monkeys on 11.04.2021.
//


#ifndef MONKEYS_LOGGER_HPP
#define MONKEYS_LOGGER_HPP

#include <string>

#define LOG_ERROR_NOT_FATAL 1
#define LOG_WARN 2
#define LOG_ERROR_FATAL 3
#define LOG_INFO 4


class IWriteToLog
{
public:
    unsigned int virtual OpenLog() = 0;
    unsigned int virtual CloseLog() = 0;
    unsigned int virtual WriteLog(const char *errorMessage) = 0;
};

class Database : public IWriteToLog
{
public:
    unsigned int OpenLog() override;
    unsigned int CloseLog() override;
    unsigned int WriteLog(const char*errorMessage) override;
};

class LogFile : public IWriteToLog
{
private:
std::string filePath;
public:
    LogFile(std::string path);
    unsigned int OpenLog() override;
    unsigned int CloseLog() override;
    unsigned int WriteLog(const char*errorMessage) override;
};


class Logger {
private:
int LogLevel;
public:
    Logger(int LogLevel);
    void OpenLog(IWriteToLog &Log);
    void CloseLog(IWriteToLog &Log);
    void WriteLog(IWriteToLog &Log, std::string text);
};


#endif //MONKEYS_LOGGER_HPP