// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_CLIENT_HPP_
#define VISIONLIB_INCLUDE_CLIENT_HPP_

#include <string>

#include "WebApplicationClient.hpp"

class Client : public IWebApplicationClient {
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

    void setID(uint64_t _ID);
    void setPrivateKey(std::string _privateKey);
    void setCompanyName(std::string _companyName);

   private:
    uint64_t ID;
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
  std::string getTempPass(const uint64_t passID);

  void establishConnection(const char* url);
  void breakConection();

  Client::Pass getPass(uint16_t index);
  bool getIsConnected();
  bool getIsLogIn();

  void setPasses(Pass* currentPasses);
  void setIsConnected(const bool value);
  void setIslogIn(const bool value);

 private:
  uint64_t ID;
  Pass* passes;
  uint16_t passesCount;
  std::string name;
  std::string password;
  bool isConnected;
  bool isLogin;
};

#endif  // VISIONLIB_INCLUDE_CLIENT_HPP_
