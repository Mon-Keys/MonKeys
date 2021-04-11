//
// Created by Monkeys on 11.04.2021.
//

#ifndef MONKEYS_CLIENT_HPP
#define MONKEYS_CLIENT_HPP

#include <std::string>

class Client {
 public:
    void logIn();
    void logOut();
    void registerClient();
    void getPasses();
    void getTempPass();
 private:
    class Pass {
     public:
        void getTempCode();
     private:
        std::string privateKey;
        std::string companyName;
        std::string tempCode;
    };

    void serverRequest();
    void establishConnection();

    long ID;
    Pass *passes;
    std::string name;
    bool isLogin;
};

#endif //MONKEYS_CLIENT_HPP