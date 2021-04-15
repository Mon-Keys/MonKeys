// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "../include/Logger.hpp"

uint16_t Database::OpenLog() { return LOG_MOCK; }

uint16_t Database::CloseLog() { return LOG_MOCK; }

uint16_t Database::WriteLog(const char *errorMessage) { return LOG_MOCK; }

bool Database::isConnected() { return false; }

Database::~Database() {}

Database::Database() {}

uint16_t LogFile::OpenLog() { return LOG_MOCK; }

uint16_t LogFile::CloseLog() { return LOG_MOCK; }

uint16_t LogFile::WriteLog(const char *errorMessage) { return LOG_MOCK; }

bool LogFile::isOpen() { return false; }

LogFile::~LogFile() {}

LogFile::LogFile(std::string path) {}

void Logger::CloseLog(const IWriteToLog &Log) {}

void Logger::OpenLog(const IWriteToLog &Log) {}

void Logger::WriteLog(const IWriteToLog &Log, std::string text) {}

Logger::Logger(int LogLevel) {}

Logger::~Logger() {}