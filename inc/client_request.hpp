//
// Created by Monkeys on 11.04.2021.
//

#ifndef MONKEYS_CLIENT_REQUEST_HPP
#define MONKEYS_CLIENT_REQUEST_HPP

class ClientRequest {
public:
    void getClientDataFromDB();
    void getPassDataFromDB();
    void getCompanyDataFromDB();
    void logInClient();
    void logOutClient();
    void registerClient();
    void getTimeCode();
private:
};

#endif //MONKEYS_CLIENT_REQUEST_HPP
