//
// Created by Monkeys on 11.04.2021.
//

#include "../include/httpClient.hpp"

HttpClient::HttpClient() {

}

HttpClient::~HttpClient() {

}

void HttpClient::logIn() {

}

void HttpClient::logOut() {

}

void HttpClient::registerClient() {

}

void HttpClient::requestPasses() {

}

std::string HttpClient::getTempPass(const long passID) {
    HttpClient::Pass currentPass = getPass(passID);
    currentPass.requestTempCode();
}

void HttpClient::establishConnection(const char *url) {

}

void HttpClient::breakConection() {

}

bool HttpClient::getIsConnected() {

}

bool HttpClient::getIsLogIn() {

}

HttpClient::Pass HttpClient::getPass(int index) {

}

void HttpClient::setIsConnected(const bool value) {

}

void HttpClient::setIslogIn(const bool value) {

}

void HttpClient::Pass::requestTempCode() {

}

void HttpClient::Pass::getID() {

}

void HttpClient::Pass::setID(long _ID) {

}

void HttpClient::Pass::setPrivateKey(std::string _privateKey) {

}

void HttpClient::Pass::setCompanyName(std::string _companyName) {

}
