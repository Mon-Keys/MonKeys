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
#include <string>
#include <vector>
// #include <pqxx/pqxx>

class ClientDB {
 private:
  uint64_t ID;
  std::string login;
  std::string password;
  uint64_t* passes;

 public:
};

class PassDB {
 private:
  uint64_t ID;
  std::string privateKey;
  uint64_t companyID;

 public:
};

class CompanyDB {
 private:
  uint64_t ID;
  std::string name;

 public:
};

class PassageDB {
 private:
  uint64_t ID;
  time_t time;
  uint8_t actionType;
  uint64_t PassID;

 public:
};

class DataBaseConnection {
 public:
  virtual bool logIn(std::string username, std::string password) {
    return true;
  }
  virtual bool logOut(std::string username) { return true; }
  virtual bool login(std::string username, std::string password) {
    return true;
  }

 private:
};

class DataBase {
 public:
  // Конектится к базе данных, создается объет таблицы
  DataBase();

  ~DataBase();

  bool insertPass(PassDB& PassID);
  bool insertPassage(PassageDB& PassageID);
  bool insertClient(ClientDB& ClientID);
  bool insertCompany(CompanyDB& CompanyID);

  bool deletePass(uint64_t PassID);
  bool deletePassage(uint64_t PassageID);
  bool deletePass(uint64_t CompanyID, uint64_t ClientID);
  bool deleteClient(uint64_t ClientID);
  bool deleteCompany(uint64_t CompanyID);

  bool PassExists(uint64_t PassID);
  bool ClientExists(uint64_t ClientID);
  bool CompanyExists(uint64_t CompanyID);
  bool PassageExists(uint64_t PassageID);

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

  PassDB getPass(std::string PassID);
  PassDB getPassage(std::string PassageID);
  ClientDB getClient(std::string ClientID);
  CompanyDB getCompany(std::string CompanyID);

 private:
  void do_modifying_request(const std::string& sql_request);
  // pqxx::result do_select_request(const std::string& sql_request);
};

#endif  // VISIONLIB_INCLUDE_ORM_HPP_
