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
 public:
  ClientDB() = default;

  explicit ClientDB(uint64_t _ID, std::string _login, std::string _email,
                    std::string _password)
      : ID(_ID), login(_login), email(_email), password(_password) {}

  ClientDB(const ClientDB& p) = default;

  ~ClientDB() = default;

  uint64_t getID() { return ID; }
  std::string getLogin() { return login; }
  std::string getEmail() { return email; }
  std::string getPassword() { return password; }

  void setID(uint64_t _ID) { ID = _ID; }
  void setLogin(std::string _login) { login = _login; }
  void setEmail(std::string _email) { email = _email; }
  void setPassword(std::string _password) { password = _password; }

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

  explicit PassageDB(uint64_t _ID, time_t _time,
                    uint8_t _actionType,
                    uint64_t _PassID)
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

class DataBaseConnect {
 public:
  DataBaseConnect() {}

  // explicit DataBaseConnect(std::map<std::string, std::string>& db_settings);

  virtual ~DataBaseConnect() {}

  virtual bool logIn(std::string username, std::string password) {
    return true;
  }

  virtual bool logOut(std::string username) { return true; }

  virtual bool is_opened() { return true; }

  virtual void sqlReq(std::string sql_request) {}

  uint64_t sql_req_for_insert(const std::string& sql_request);

 protected:
  // std::unique_ptr<pqxx::connection> database_;
  std::string str_db_settings;

 private:
};

class PassDataBase : public DataBaseConnect {
 public:
  PassDataBase() = default;

  // explicit PassDataBase((std::map<std::string, std::string> & db_settings));

  virtual ~PassDataBase() = default;

  uint64_t insertPass(const PassDB& Pass);
  bool deletePass(const uint64_t PassID);
  bool PassExists(const uint64_t PassID);
  std::vector<PassDB> getAllPasses(const std::string& sql_limit,
                                   const std::string& sql_offset);
  std::vector<PassDB> getClientsPasses(const uint64_t ClientID);
  std::vector<PassDB> getCompanysPasses(const uint64_t CompanyID);
  PassDB getPass(const uint64_t PassID);

 private:
  void do_modifying_request(const std::string& sql_request);
  std::vector<PassDB> sqlReq(const std::string& sql_request);
  // pqxx::result do_select_request(const std::string& sql_request);
};

class ClientDataBase : public DataBaseConnect {
 public:
  ClientDataBase() = default;

  // explicit ClientDataBase((std::map<std::string, std::string> &
  // db_settings));

  virtual ~ClientDataBase() = default;

  uint64_t insertClient(const ClientDB& Pass);
  bool deleteCLient(const uint64_t ClientID);
  bool ClientExists(const uint64_t ClientID);
  std::vector<ClientDB> getAllClients(const std::string& sql_limit,
                                      const std::string& sql_offset);
  ClientDB getClient(const uint64_t ClientID);

 private:
  void do_modifying_request(const std::string& sql_request);
  std::vector<ClientDB> sqlReq(const std::string& sql_request);
  // pqxx::result do_select_request(const std::string& sql_request);
};

class CompanyDataBase : public DataBaseConnect {
 public:
  CompanyDataBase() = default;

  // explicit CompanyDataBase((std::map<std::string, std::string> &
  // db_settings));

  virtual ~CompanyDataBase() = default;

  uint64_t insertCompany(const CompanyDB& Company);
  bool deleteCompany(const uint64_t CompanyID);
  bool CompanyExists(const uint64_t CompanyID);
  std::vector<CompanyDB> getAllCompanys(const std::string& sql_limit,
                                        const std::string& sql_offset);
  CompanyDB getCompany(const uint64_t CompanyID);

 private:
  void do_modifying_request(const std::string& sql_request);
  std::vector<CompanyDB> sqlReq(const std::string& sql_request);
  // pqxx::result do_select_request(const std::string& sql_request);
};

class PassageDataBase : public DataBaseConnect {
 public:
  PassageDataBase() = default;

  // explicit PassageDataBase((std::map<std::string, std::string> &
  // db_settings));

  virtual ~PassageDataBase() = default;

  uint64_t insertPassage(const PassageDB& Passage);
  bool deletePassage(const uint64_t PassageID);
  bool PassageExists(const uint64_t PassageID);
  std::vector<PassageDB> getAllPassages(const std::string& sql_limit,
                                        const std::string& sql_offset);
  std::vector<PassageDB> getPassesPassages(const uint64_t PassID);
  PassageDB getPassage(const uint64_t PassageID);

 private:
  void do_modifying_request(const std::string& sql_request);
  std::vector<PassageDB> sqlReq(const std::string& sql_request);
  // pqxx::result do_select_request(const std::string& sql_request);
};

#endif  // VISIONLIB_INCLUDE_ORM_HPP_
