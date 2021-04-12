//
// Created by Monkeys on 11.04.2021.
//

#ifndef MONKEYS_HTTPSERVER_HPP
#define MONKEYS_HTTPSERVER_HPP

class ClientRequest {
    void waitRequest();
    void waitConnection();
    void reply();
};

#endif //MONKEYS_HTTPSERVER_HPP
