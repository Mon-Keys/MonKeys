//
// Created by Monkeys on 11.04.2021.
//

#ifndef MONKEYS_TERMINALSERVER_HPP
#define MONKEYS_TERMINALSERVER_HPP

class TerminalServer {
public:
    void getClientDataFromDB();
    void getPassDataFromDB();
    void getCompanyDataFromDB();
    void generateTimeCode();
    void compareTimeCode();
private:
};

#endif //MONKEYS_TERMINALSERVER_HPP
