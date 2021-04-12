// Copyright 2021 Monkeys

#ifndef VISIONLIB_INCLUDE_CLIENTSERVER_HPP
#define VISIONLIB_INCLUDE_CLIENTSERVER_HPP

#include <ctime>
#include <string>

class ClientServer {
 public:
    void getClientDataFromDB(long ID);
    void getPassDataFromDB(long PassID);
    void getCompanyDataFromDB(long CompanyID);
    void logInClient(std::string Login, std::string Password);
    void logOutClient(long ClientID);
    void registerClient(std::string Login, std::string Password);
    void getTimeCode(long PassID);
 private:
};

#endif //VISIONLIB_INCLUDE_CLIENTSERVER_HPP