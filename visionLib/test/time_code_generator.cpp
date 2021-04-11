#include "gtest/gtest.h"
#include "../include/time_code_generator.hpp"

TEST(TimeCodeGeneratorTest, correct_generate_on_one_time_segment) {
    TimeCodeGenerator generator;
    const std::string privateKey = "lol";
    const unsigned long passID = 2;
    const unsigned long timeStamp = time();
    std::string firstCode = generator.generateTimeCode(privateKey, passID, timeStamp);
    sleep(10);
    timeStamp = time();
    std::string secondCode = generator.generateTimeCode(privateKey, passID, timeStamp);
    EXPECT_STREQ(firstCode, secondCode);
}