//
// Created by ilyagu on 11.04.2021.
//

#ifndef MONKEYS_TIME_CODE_GENERATOR_HPP
#define MONKEYS_TIME_CODE_GENERATOR_HPP

#include <iostream>
#include <string>

class TimeCodeGenerator {

private: 
    std::string privateKey;
    unsigned long PassID;
    unsigned long timeStamp;
    unsigned short timeInterval;

    // startTime --- UNIX0
    
    std::string getHashedOTP();
    unsigned long getTParameter();
    void updateTime();
public:
    TimeCodeGenerator(std::string privateKey,
                        unsigned long PassID, 
                unsigned short timeInterval);
    std::string generateTimeCode();
    TimeCodeGenerator();
    ~TimeCodeGenerator();
    TimeCodeGenerator(const TimeCodeGenerator&) = delete;
    TimeCodeGenerator(TimeCodeGenerator&&) = default;
};

#endif //MONKEYS_TIME_CODE_GENERATOR_HPP
