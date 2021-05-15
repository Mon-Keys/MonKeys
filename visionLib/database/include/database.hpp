// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_ORM_HPP_
#define VISIONLIB_INCLUDE_ORM_HPP_

#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/date_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/tokenizer.hpp>
#include <ctime>
#include <functional>
#include <iostream>
#include <map>
// #include <optional.h>
#include <chrono>
#include <pqxx/pqxx>
#include <queue>
#include <string>
#include <thread>
#include <vector>

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

  bool insertPass(const PassDB& Pass);
  bool deletePass(const uint64_t& PassID);
  bool PassExists(const uint64_t PassID);
  std::vector<PassDB> getAllPasses(const std::string& sql_limit,
                                   const std::string& sql_offset);
  std::vector<PassDB> getClientsPasses(const uint64_t ClientID);
  std::vector<PassDB> getCompanysPasses(const uint64_t CompanyID);
  PassDB getPass(const uint64_t PassID);

 private:
  void do_modifying_request(std::string& sql_request);
  pqxx::result do_select_request(std::string& sql_request);
};

class ClientDataBase : public DataBase {
 public:
  ClientDataBase() = default;

  explicit ClientDataBase(std::map<std::string, std::string>& db_settings);

  virtual ~ClientDataBase() = default;

  bool insertClient(const std::string& Login, const std::string& Email, const std::string& Password);
  bool deleteCLient(const std::string& login);
  bool ClientExists(const std::string& login);
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

  bool insertCompany(const CompanyDB& Company);
  bool deleteCompany(const uint64_t CompanyID);
  bool CompanyExists(const std::string& name);
  std::vector<CompanyDB> getAllCompanys(const std::string& sql_limit,
                                        const std::string& sql_offset);
  CompanyDB getCompany(const uint64_t CompanyID);

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
