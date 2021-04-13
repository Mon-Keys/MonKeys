// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_ORM_HPP_
#define VISIONLIB_INCLUDE_ORM_HPP_

#include <string>

class ORM {
 private:
  class ClientDB {
   public:
   private:
    uint64_t ID;
    std::string login;
    std::string password;
    uint64_t* passes;
  };
  class PassDB {
   public:
   private:
    uint64_t ID;
    std::string privateKey;
    uint64_t companyID;
  };
  class CompanyDB {
   public:
   private:
    uint64_t ID;
    std::string name;
  };

 public:
  PassDB getPassData(uint64_t ID);
  ClientDB getClientData(uint64_t ID);
  CompanyDB getCompanyData(uint64_t ID);
};

#endif  // VISIONLIB_INCLUDE_ORM_HPP_
