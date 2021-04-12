//
// Created by Monkeys on 11.04.2021.
//

#ifndef MONKEYS_CLIENT_HPP
#define MONKEYS_CLIENT_HPP

#include <string>

#include "../include/WebApplicationClient.hpp"

class Client : public WebApplicationClient {
 public:
   class Pass {
    public:
      Pass();
      ~Pass();

      Pass(const Pass&) = delete;
      Pass(Pass&&) = default;

      Pass& operator=(const Pass&) = delete;
      Pass& operator=(Pass&&) = delete;

      void requestTempCode();
      
      void getID();

      void setID(long _ID);
      void setPrivateKey(std::string _privateKey);
      void setCompanyName(std::string _companyName);
    private:
      long ID;
      std::string privateKey;
      std::string companyName;
   };

   Client();
   ~Client();

   Client(const Client&) = delete;
   Client(Client&&) = delete;

   Client& operator=(const Client&) = delete;
   Client& operator=(Client&&) = delete;

   void logIn();
   void logOut();
   void registerClient();
   void requestPasses();
   std::string getTempPass(const long passID);

   void establishConnection(const char *url);
   void breakConection();

   Client::Pass getPass(int index);
   bool getIsConnected();
   bool getIsLogIn();

   void setPasses(Pass* currentPasses);
   void setIsConnected(const bool value);
   void setIslogIn(const bool value);

 private:
   long ID;
   Pass *passes;
   int passesCount;
   std::string name;
   std::string password;
   bool isConnected;
   bool isLogin;
};

#endif //MONKEYS_CLIENT_HPP