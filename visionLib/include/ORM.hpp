// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_ORM_HPP_
#define VISIONLIB_INCLUDE_ORM_HPP_

#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>
// #include <pqxx/pqxx>

class ClientDB {
 private:
  uint64_t ID;
  std::string login;
  std::string email;
  std::string password;

 public:
  uint64_t getID() { return ID; }
  std::string getLogin() { return login; }
  std::string getEmail() { return email; }
  std::string getPassword() { return password; }

  void setID(uint64_t _ID) { ID = _ID; }
  void setLogin(std::string _login) { login = _login; }
  void setEmail(std::string _email) { email = _email; }
  void setPassword(std::string _Password) { password = _Password; }
};

class PassDB {
 private:
  uint64_t ID;
  std::string privateKey;
  uint64_t CompanyID;
  uint64_t ClientID;

 public:
  uint64_t getID() { return ID; }
  std::string getprivate() { return privateKey; }
  uint64_t getCompanyID() { return CompanyID; }
  uint64_t getClientID() { return ClientID; }

  void setID(uint64_t _ID) { ID = _ID; }
  void setprivate(std::string _privateKey) { privateKey = _privateKey; }
  void setClientID(uint64_t _CompanyID) { CompanyID = _CompanyID; }
  void setCompanyID(uint64_t _ClientID) { ClientID = _ClientID; }
};

class CompanyDB {
 private:
  uint64_t ID;
  std::string name;

 public:
  uint64_t getID() { return ID; }
  std::string getName() { return name; }

  void setID(uint64_t _ID) { ID = _ID; }
  void setName(std::string _name) { name = _name; }
};

class PassageDB {
 private:
  uint64_t ID;
  time_t time;
  uint8_t actionType;
  uint64_t PassID;

 public:
  uint64_t getID() { return ID; }
  time_t getTime() { return time; }
  uint8_t getActionType() { return actionType; }
  uint64_t getPassID() { return PassID; }

  void setID(uint64_t _ID) { ID = _ID; }
  void setTime(time_t _time) { time = _time; }
  void setActionType(uint8_t _actionType) { actionType = _actionType; }
  void setPassID(uint64_t _PassID) { PassID = _PassID; }
};

class DataBaseConnect {
 public:
  DataBaseConnect();

  ~DataBaseConnect();

  virtual bool is_opened() const;

  virtual bool logIn(std::string username, std::string password) {
    return true;
  }
  virtual bool logOut(std::string username) { return true; }
  virtual bool login(std::string username, std::string password) {
    return true;
  }

 protected:
  // std::unique_ptr<pqxx::connection> database_;
  std::string str_db_settings;

 private:
};

class DataBase {
 public:
  // Конектится к базе данных, создается объет таблицы

  uint64_t insertPass(const PassDB& Pass);
  uint64_t insertPassage(const PassageDB& Passage);
  uint64_t insertClient(const ClientDB& Client);
  uint64_t insertCompany(const CompanyDB& Company);

  bool deletePass(const uint64_t PassID);
  bool deletePassage(const uint64_t PassageID);
  bool deletePass(const uint64_t CompanyID, uint64_t ClientID);
  bool deleteClient(const uint64_t ClientID);
  bool deleteCompany(const uint64_t CompanyID);

  bool PassExists(const uint64_t PassID);
  bool ClientExists(const uint64_t ClientID);
  bool CompanyExists(const uint64_t CompanyID);
  bool PassageExists(const uint64_t PassageID);

  std::vector<PassDB> getAllPasses(const std::string& sql_limit,
                                   const std::string& sql_offset);
  std::vector<PassageDB> getAllPassages(const std::string& sql_limit,
                                        const std::string& sql_offset);
  std::vector<ClientDB> getAllClients(const std::string& sql_limit,
                                      const std::string& sql_offset);
  std::vector<CompanyDB> getAllCompanys(const std::string& sql_limit,
                                        const std::string& sql_offset);
  std::vector<PassDB> getClientsPasses(const uint64_t ClientID);
  std::vector<PassDB> getCompanysPasses(const uint64_t CompanyID);
  std::vector<PassageDB> getPassesPassages(const uint64_t PassID);

  PassDB getPass(const uint64_t PassID);
  PassageDB getPassage(const uint64_t PassageID);
  ClientDB getClient(const uint64_t ClientID);
  CompanyDB getCompany(const uint64_t CompanyID);

  template <class T>
  std::vector<T> sql_req(const std::string& sql_request);

 private:
  void do_modifying_request(const std::string& sql_request);
  // pqxx::result do_select_request(const std::string& sql_request);
};

#endif  // VISIONLIB_INCLUDE_ORM_HPP_
