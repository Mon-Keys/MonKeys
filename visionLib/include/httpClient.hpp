//
// Created by Monkeys on 11.04.2021.
//

#ifndef MONKEYS_CLIENT_HPP
#define MONKEYS_CLIENT_HPP

#include <string>

class HttpClient {
 public:
   ~HttpClient();
   HttpClient();

   HttpClient(const HttpClient&) = delete;
   HttpClient(HttpClient&&) = delete;

   HttpClient& operator=(const HttpClient&) = delete;
   HttpClient& operator=(HttpClient&&) = delete;

   void logIn();
   void logOut();
   void registerClient();
   void getPasses();
   void getTempPass();

   void serverRequest();
   void establishConnection(const char *url);
   void breakConection();

   bool getIsConnected();
   bool getIsLogIn();

   void setIsConnectde(const bool value);
   void setIslogIn(const bool value);
   void setPasses(long *passesFromBD);

 private:
   class Pass {
    public:
      void getTempCode();
    private:
      std::string privateKey;
      std::string companyName;
      std::string tempCode;
   };

   long ID;
   Pass *passes;
   std::string name;
   bool isConnected;
   bool isLogin;
};

#endif //MONKEYS_CLIENT_HPP