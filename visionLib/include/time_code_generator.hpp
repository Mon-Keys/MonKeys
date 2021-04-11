//
// Created by ilyagu on 11.04.2021.
//

#ifndef MONKEYS_TIME_CODE_GENERATOR_HPP
#define MONKEYS_TIME_CODE_GENERATOR_HPP

#include <iostream>
#include <string>

class TimeCodeGenerator {
public:
    TimeCodeGenerator();
    ~TimeCodeGenerator();
    std:string generateTimeCode(std::string privateKey, unsigned long PassID, unsigned long timeStamp);
};

#endif //MONKEYS_TIME_CODE_GENERATOR_HPP
