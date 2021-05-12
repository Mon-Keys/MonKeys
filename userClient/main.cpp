// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "TimeCodeGenerator.hpp"

int main()
{
    uint64_t PassID = 1;
    uint16_t timeInterval = 30;
    uint64_t timeStamp = 164334343;
    uint64_t companyID = 1;
    std::string userKey = "JBSWdssdsK3PXPK3PXP";
    TimeCodeGenerator codegen(userKey, PassID, companyID, timeInterval);
    codegen.generateTimeCode();
}
