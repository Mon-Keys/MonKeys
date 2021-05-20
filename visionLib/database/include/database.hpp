// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_ORM_HPP_
#define VISIONLIB_INCLUDE_ORM_HPP_

#include "tables.hpp"

class DataBase {
 public:
  DataBase();

  explicit DataBase(std::map<std::string, std::string>& db_settings);

  virtual ~DataBase(){};

  virtual bool is_opened() const;

 protected:
  std::unique_ptr<pqxx::connection> database_;
  std::string str_db_settings;

 private:
};

class PassDataBase : public DataBase {
 public:
  PassDataBase() = default;

  explicit PassDataBase(std::map<std::string, std::string>& db_settings);

  virtual ~PassDataBase() = default;

  uint64_t insertPass(const std::string& private_key, const uint64_t& CompanyID,
                      const uint64_t& ClientID);
  bool deletePass(const uint64_t& PassID);
  bool PassExists(const uint64_t& PassID);
  bool PassExists(const uint64_t& ClientID, const uint64_t& CompanyID);
  std::vector<PassDB> getAllPasses(const std::string& sql_limit,
                                   const std::string& sql_offset);
  std::vector<PassDB> getClientsPasses(const uint64_t& ClientID);
  std::vector<PassDB> getCompanysPasses(const uint64_t& CompanyID);
  PassDB getPass(const uint64_t& PassID);

 private:
  void do_modifying_request(std::string& sql_request);
  pqxx::result do_select_request(std::string& sql_request);
};

class ClientDataBase : public DataBase {
 public:
  ClientDataBase() = default;

  explicit ClientDataBase(std::map<std::string, std::string>& db_settings);

  virtual ~ClientDataBase() = default;

  uint64_t insertClient(const std::string& Login, const std::string& Email,
                        const std::string& Password);
  bool deleteCLient(const std::string& login);
  bool ClientExists(const std::string& login);
  bool ClientExists(const uint64_t& ClientID);
  std::vector<ClientDB> getAllClients(const std::string& sql_limit,
                                      const std::string& sql_offset);
  ClientDB getClient(const std::string login);

 private:
  void do_modifying_request(std::string& sql_request);
  pqxx::result do_select_request(std::string& sql_request);
};

class CompanyDataBase : public DataBase {
 public:
  CompanyDataBase() = default;

  explicit CompanyDataBase(std::map<std::string, std::string>& db_settings);

  virtual ~CompanyDataBase() = default;

  uint64_t insertCompany(const std::string& name);
  bool deleteCompany(const std::string& name);
  bool CompanyExists(const std::string& name);
  std::vector<CompanyDB> getAllCompanys(const std::string& sql_limit,
                                        const std::string& sql_offset);
  CompanyDB getCompany(const std::string& CompanyName);

 private:
  void do_modifying_request(std::string& sql_request);
  pqxx::result do_select_request(std::string& sql_request);
};

class PassageDataBase : public DataBase {
 public:
  PassageDataBase() = default;

  explicit PassageDataBase(std::map<std::string, std::string>& db_settings);

  virtual ~PassageDataBase() = default;

  bool insertPassage(const PassageDB& Passage);
  bool deletePassage(const uint64_t& PassageID);
  bool PassageExists(const uint64_t& PassageID);
  std::vector<PassageDB> getAllPassages(const std::string& sql_limit,
                                        const std::string& sql_offset);
  std::vector<PassageDB> getPassesPassages(const uint64_t PassID);
  PassageDB getPassage(const uint64_t PassageID);

 private:
  void do_modifying_request(std::string& sql_request);
  pqxx::result do_select_request(std::string& sql_request);
};

#endif  // VISIONLIB_INCLUDE_ORM_HPP_
