// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "../include/Terminal.hpp"

Terminal::Terminal(TempCode _tempCode, std::string _ID, bool isConnected) {};
Terminal::Terminal() {}
Terminal::~Terminal() {}
Terminal::TempCode::TempCode(std::string _tempCode, bool isValid) {};
Terminal::TempCode::TempCode() {}
Terminal::TempCode::~TempCode() {}

void Terminal::open() {}
void Terminal::serverRequest() {}
void Terminal::establishConnection(const char* url) {}
bool Terminal::getIsConnected() { return true; }
void Terminal::setCompanyID(std::string companyID) {}
void Terminal::checkTempCodeValidity () {}
std::string Terminal::getCompanyID(){}
Terminal::TempCode Terminal::getCurrentTempCode(){};
std::string Terminal::readTimeCode() {}
std::string Terminal::TempCode::getTempCode() {}
void Terminal::TempCode::setTempCode(std::string readTempCode) {}
bool Terminal::TempCode::isTempCodeValid() {}
