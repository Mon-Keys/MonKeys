//
// Created by Monkeys on 11.04.2021.
//

#ifndef MONKEYS_TERMINAL_SERVER_HPP
#define MONKEYS_TERMINAL_SERVER_HPP

class TerminalServer {
public:
    void waitRequest();
    void waitConnection();
    void reply();
};

#endif //MONKEYS_TERMINAL_SERVER_HPP
