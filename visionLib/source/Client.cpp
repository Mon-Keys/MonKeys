// Copyright 2021 MonKeys

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
}
void Client::establishConnection(const char *url) {}
void Client::breakConection() {}
bool Client::getIsConnected() {}
bool Client::getIsLogIn() {}
Client::Pass Client::getPass(uint16_t index) {}
void Client::setIsConnected(const bool value) {}
void Client::setIslogIn(const bool value) {}
void Client::Pass::requestTempCode() {}
void Client::Pass::getID() {}
void Client::Pass::setID(uint64_t ID) {}
void Client::Pass::setPrivateKey(std::string _privateKey) {}
void Client::Pass::setCompanyName(std::string _companyName) {}
