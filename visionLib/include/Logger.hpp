<<<<<<< HEAD
// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_LOGGER_HPP_
#define VISIONLIB_INCLUDE_LOGGER_HPP_

#include <string>

#define LOG_ERROR_NOT_FATAL 1
#define LOG_WARN 2
#define LOG_ERROR_FATAL 3
#define LOG_INFO 4
#define LOG_MOCK 5

class IWriteToLog {
 public:
  uint16_t virtual OpenLog() = 0;
  uint16_t virtual CloseLog() = 0;
  uint16_t virtual WriteLog(const char *errorMessage) = 0;
};

class Database : public IWriteToLog {
 private:
  void connect();

 public:
  bool isConnected();
  Database();
  ~Database();
  uint16_t OpenLog() override;
  uint16_t CloseLog() override;
  uint16_t WriteLog(const char *errorMessage) override;
};

class LogFile : public IWriteToLog {
 private:
  std::string filePath;

 public:
  explicit LogFile(std::string path);
  ~LogFile();
  bool isOpen();
  uint16_t OpenLog() override;
  uint16_t CloseLog() override;
  uint16_t WriteLog(const char *errorMessage) override;
};

class Logger {
 private:
  int LogLevel;

 public:
  explicit Logger(int LogLevel);
  ~Logger();
  void OpenLog(const IWriteToLog &Log);
  void CloseLog(const IWriteToLog &Log);
  void WriteLog(const IWriteToLog &Log, std::string text);
};

#endif  // VISIONLIB_INCLUDE_LOGGER_HPP_
=======
>>>>>>> 604e7b1a12f46225ef2f1bb28b9c47f50695f080
