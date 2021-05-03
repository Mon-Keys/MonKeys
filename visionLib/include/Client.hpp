<<<<<<< HEAD
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
    Pass(uint64_t _ID, std::string _privateKey, std::string _companyName);
    ~Pass();

    Pass(const Pass&) = delete;
    Pass(Pass&&) = default;

    Pass& operator=(const Pass&) = delete;
    Pass& operator=(Pass&&) = delete;

    // запрос на генерацию временного кода по privateKey пропуска
    std::string requestTempCode();

    // гетеры
    void getID();
    void getPrivateKey();
    void getCompanyName();

    // сетеры
    void setID(uint64_t _ID);
    void setPrivateKey(std::string _privateKey);
    void setCompanyName(std::string _companyName);

   private:
    uint64_t ID;
    std::string privateKey;
    std::string companyName;
  };

  Client();
  Client(uint64_t _ID, Pass* _passes, uint16_t _passesCount, std::string _name,
         std::string _password, bool _isConnected = false,
         bool _isLogin = false);
  ~Client();

  Client(const Client&) = delete;
  Client(Client&&) = delete;

  Client& operator=(const Client&) = delete;
  Client& operator=(Client&&) = delete;

  // авторизация пользователя
  void logIn() override;
  // выход пользователя из аккаунта
  void logOut() override;
  // регистрация пользователя
  void registerClient() override;
  // запрос на выдачу всех пропусков пользователя
  void requestPasses() override;
  // получение временного кода по выбранному пропуску
  std::string getTempPass(const uint64_t passID) override;

  // установление соединения
  void establishConnection(const char* url) override;
  // разрыв соединения
  void breakConnection() override;

  // гетеры
  uint64_t getID();
  Pass* getPasses();
  uint16_t getPassesCount();
  std::string getName();
  Pass getPass(uint64_t index);
  bool getIsConnected();
  bool getIsLogIn();

  // сетеры
  void setID(uint64_t _ID);
  void setPasses(Pass* currentPasses);
  void setPassesCount(uint16_t _passesCount);
  void setName(std::string _name);
  void setIsConnected(const bool value);
  void setIsLogIn(const bool value);

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
=======
>>>>>>> 604e7b1a12f46225ef2f1bb28b9c47f50695f080
