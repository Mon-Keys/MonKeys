// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_TABLES_HPP_
#define VISIONLIB_INCLUDE_TABLES_HPP_

#include <iostream>
#include <string>
#include <map>
#include <optional>
#include <queue>
#include <functional>
#include <ctime>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/date_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <pqxx/pqxx>

class ClientDB {
 public:
  ClientDB() = default;

  explicit ClientDB(uint64_t _ID,
                    std::string _login,
                    std::string _email,
                    std::string _password) 
          : ID(_ID), login(_login), 
          email(_email), password(_password) {}

  ClientDB(const ClientDB& p) = default;

  ~ClientDB() = default;

  uint64_t getID() { return ID; }
  std::string getLogin() { return login; }
  std::string getEmail() { return email; }
  std::string getPassword() { return password; }

  void setID(uint64_t _ID) { ID = _ID; }
  void setLogin(std::string _login) { login = _login; }
  void setEmail(std::string _email) { email = _email; }
  void setPassword(std::string _Password) { password = _Password; }

 private:
  uint64_t ID;
  std::string login;
  std::string email;
  std::string password;
};

class PassDB {
 public:
  PassDB() = default;

  explicit PassDB(uint64_t _ID, std::string _privateKey, uint64_t _CompanyID,
         uint64_t _ClientID)
      : ID(_ID),
        privateKey(_privateKey),
        CompanyID(_CompanyID),
        ClientID(_ClientID) {}

  PassDB(const PassDB& p) = default;

  ~PassDB() = default;

  uint64_t getID() { return ID; }
  std::string getprivate() { return privateKey; }
  uint64_t getCompanyID() { return CompanyID; }
  uint64_t getClientID() { return ClientID; }

  void setID(uint64_t _ID) { ID = _ID; }
  void setprivate(std::string _privateKey) { privateKey = _privateKey; }
  void setClientID(uint64_t _CompanyID) { CompanyID = _CompanyID; }
  void setCompanyID(uint64_t _ClientID) { ClientID = _ClientID; }

 private:
  uint64_t ID;
  std::string privateKey;
  uint64_t CompanyID;
  uint64_t ClientID;
};

class CompanyDB {
 public:
  CompanyDB() = default;

  explicit CompanyDB(uint64_t _ID, std::string _name) : ID(_ID), name(_name) {}

  CompanyDB(const CompanyDB& p) = default;

  ~CompanyDB() = default;

  uint64_t getID() { return ID; }
  std::string getName() { return name; }

  void setID(uint64_t _ID) { ID = _ID; }
  void setName(std::string _name) { name = _name; }

 private:
  uint64_t ID;
  std::string name;
};

class PassageDB {
 public:
  PassageDB() = default;

  explicit PassageDB(uint64_t _ID, time_t _time, uint8_t _actionType, uint64_t _PassID)
      : ID(_ID), time(_time), actionType(_actionType), PassID(_PassID) {}

  PassageDB(const PassageDB& p) = default;

  ~PassageDB() = default;

  uint64_t getID() { return ID; }
  time_t getTime() { return time; }
  uint8_t getActionType() { return actionType; }
  uint64_t getPassID() { return PassID; }

  void setID(uint64_t _ID) { ID = _ID; }
  void setTime(time_t _time) { time = _time; }
  void setActionType(uint8_t _actionType) { actionType = _actionType; }
  void setPassID(uint64_t _PassID) { PassID = _PassID; }

 private:
  uint64_t ID;
  time_t time;
  uint8_t actionType;
  uint64_t PassID;
};

#endif // VISIONLIB_INCLUDE_TABLES_HPP_