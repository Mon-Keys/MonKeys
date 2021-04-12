//
// Created by Monkeys on 11.04.2021.
//

#include "../include/Client.hpp"

Client::Client() {

}

Client::~Client() {

}

void Client::logIn() {

}

void Client::logOut() {

}

void Client::registerClient() {

}

void Client::requestPasses() {

}

std::string Client::getTempPass(const long passID) {
    Client::Pass currentPass = getPass(passID);
    currentPass.requestTempCode();
}

void Client::establishConnection(const char *url) {

}

void Client::breakConection() {

}

bool Client::getIsConnected() {

}

bool Client::getIsLogIn() {

}

Client::Pass Client::getPass(int index) {

}

void Client::setIsConnected(const bool value) {

}

void Client::setIslogIn(const bool value) {

}

void Client::Pass::requestTempCode() {

}

void Client::Pass::getID() {

}

void Client::Pass::setID(long _ID) {

}

void Client::Pass::setPrivateKey(std::string _privateKey) {

}

void Client::Pass::setCompanyName(std::string _companyName) {

}
