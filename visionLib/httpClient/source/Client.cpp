// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "Client.hpp"

Client::Client() {}
Client::Client(uint64_t _ID, Pass* _passes, uint16_t _passesCount,
               std::string _name, std::string _password, bool _isConnected,
               bool _isLogin) {}
Client::~Client() {}

void Client::logIn() {}
void Client::logOut() {}
void Client::registerClient() {}
void Client::requestPasses() {}
std::string Client::getTempPass(uint64_t passID) { return ""; }

void Client::establishConnection(const char* url) {}
void Client::breakConnection() {}

uint64_t Client::getID() { return 1; }
Client::Pass* Client::getPasses() {
  Pass* currentPasses = nullptr;
  return currentPasses;
}
uint16_t Client::getPassesCount() { return 1; }
std::string Client::getName() { return ""; }
bool Client::getIsConnected() { return false; }
bool Client::getIsLogIn() { return false; }
Client::Pass Client::getPass(uint64_t index) { return Pass(); }

void Client::setID(uint64_t ID) {}
void Client::setPasses(Pass* currentPasses) {}
void Client::setPassesCount(uint16_t _passesCount) {}
void Client::setName(std::string _name) {}
void Client::setIsConnected(const bool value) {}
void Client::setIsLogIn(const bool value) {}

Client::Pass::Pass() {}
// cppcheck-suppress uninitMemberVar
Client::Pass::Pass(uint64_t _ID, std::string _privateKey,
                   std::string _companyName) {}
Client::Pass::~Pass() {}

std::string Client::Pass::requestTempCode() { return ""; }
void Client::Pass::getID() {}
void Client::Pass::getPrivateKey() {}
void Client::Pass::getCompanyName() {}
void Client::Pass::setID(uint64_t ID) {}
void Client::Pass::setPrivateKey(std::string _privateKey) {}
void Client::Pass::setCompanyName(std::string _companyName) {}
