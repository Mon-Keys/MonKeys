// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "../include/Client.hpp"

Client::Client() {}
Client::~Client() {}
void Client::logIn() {}
void Client::logOut() {}

void Client::registerClient() {}
void Client::requestPasses() {}
std::string Client::getTempPass(uint64_t passID) {
  Client::Pass currentPass = getPass(passID);
  currentPass.requestTempCode();
  return "";
}
void Client::establishConnection(const char *url) {}
void Client::breakConection() {}
bool Client::getIsConnected() { return false; }
bool Client::getIsLogIn() { return false; }
Client::Pass Client::getPass(uint16_t index) { return Pass(); }
void Client::setPasses(Pass* currentPasses) {}
void Client::setIsConnected(const bool value) {}
void Client::setIslogIn(const bool value) {}
void Client::Pass::requestTempCode() {}
void Client::Pass::getID() {}
void Client::Pass::setID(uint64_t ID) {}
void Client::Pass::setPrivateKey(std::string _privateKey) {}
void Client::Pass::setCompanyName(std::string _companyName) {}

Client::Pass::Pass() {}
Client::Pass::~Pass() {}
