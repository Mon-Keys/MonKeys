// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "TimeCodeGenerator.hpp"

int main() {
  uint64_t PassID = 1544716917;
  uint16_t timeInterval = 30;
  uint64_t companyID = 13303233;
  std::string userKey = "dsdsdCdsdsdsgfwegvwevwerweQRBBX";
  TimeCodeGenerator codegen(userKey, PassID, companyID, timeInterval);
  std::cout << std::time(0) << std::endl;
  std::vector<std::string> result = codegen.generateTimeCodesAhead(5);
  for (int i = 0; i < 5; i++) {
    std::cout << i << ": " <<result[i] << std::endl;
  }
  while (true) {
    std::string timecode = codegen.generateTimeCode();
    std::cout << timecode << std::endl;
    TimeCode tc(timecode);
    std::cout << tc.isValid() << std::endl;
    std::cout << tc.getCompanyID() << std::endl;
    std::cout << tc.getPassID() << std::endl;
    sleep(5);
  }
}
