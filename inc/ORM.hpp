//
// Created by ilyagu on 11.04.2021.
//

#ifndef MONKEYS_ORM_HPP
#define MONKEYS_ORM_HPP

#include <std::string>

class ORM {
 public:
    void getPassData();
    void getClientData();
    void getCompanyData();
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
};

#endif //MONKEYS_ORM_HPP
