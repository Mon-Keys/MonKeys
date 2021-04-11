//
// Created by Monkeys on 11.04.2021.
//

#ifndef MONKEYS_TERMINAL_REQUEST_HPP
#define MONKEYS_TERMINAL_REQUEST_HPP

class TerminalRequest {
public:
    void getClientDataFromDB();
    void getPassDataFromDB();
    void getCompanyDataFromDB();
    void generateTimeCode();
    void compareTimeCode();
private:
};

#endif //MONKEYS_TERMINAL_REQUEST_HPP
