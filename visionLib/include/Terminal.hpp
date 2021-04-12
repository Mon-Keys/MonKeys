//
// Created by Monkeys on 11.04.2021.
//

#ifndef MONKEYS_TERMINAL_HPP
#define MONKEYS_TERMINAL_HPP

class Terminal {
 public:
    void open();
    void readTimeCode();
 private:
    void serverRequest();
    void establishConnection();

    long ID;

};

#endif //MONKEYS_TERMINAL_HPP
