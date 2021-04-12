//
// Created by ilyagu on 11.04.2021.
//

#ifndef MONKEYS_ORM_HPP
#define MONKEYS_ORM_HPP

#include <string>

class ORM {
 private:
    class ClientDB {
     public:
     private:
        long ID;
        std::string login;
        std::string password;
        long * passes;
    };
    class PassDB {
     public:
     private:
        long ID;
        std::string privateKey;
        long companyID;
    };
    class CompanyDB {
     public:
     private:
        long ID;
        std::string name;
    };
 public:
    PassDB getPassData(long ID);
    ClientDB getClientData(long ID);
    CompanyDB getCompanyData(long ID);
};

#endif //MONKEYS_ORM_HPP