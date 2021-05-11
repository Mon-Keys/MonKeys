// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_ORM_HPP_
#define VISIONLIB_INCLUDE_ORM_HPP_

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

#include "tables.hpp"

class DataBase {
 public:
  DataBase() {};

  explicit DataBase(std::map<std::string, std::string>& db_settings);

  virtual ~DataBase() {};

  virtual bool logIn(std::string username, std::string password) {
    return true;
  }

  virtual bool logOut(std::string username) { return true; }

  virtual bool is_opened() { return true;};

  virtual void sqlReq(std::string sql_request) {};

  uint64_t sql_req_for_insert(const std::string& sql_request);

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
  pqxx::result do_select_request(const std::string& sql_request);
};

class ClientDataBase : public DataBase {
 public:
  ClientDataBase() = default;

  explicit ClientDataBase(std::map<std::string, std::string>& db_settings);

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
  pqxx::result do_select_request(const std::string& sql_request);
};

class CompanyDataBase : public DataBase {
 public:
  CompanyDataBase() = default;

  explicit CompanyDataBase(std::map<std::string, std::string>& db_settings);

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
  pqxx::result do_select_request(const std::string& sql_request);
};

class PassageDataBase : public DataBase {
 public:
  PassageDataBase() = default;

  explicit PassageDataBase(std::map<std::string, std::string>& db_settings);

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
  pqxx::result do_select_request(const std::string& sql_request);
};

class ClientHandlers {

public:
    ClientHandlers() : _db() {};

    std::string all_clients(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string one_client(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string delete_client(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string insert_client(const std::string& id_request, const std::map<std::string, size_t>& args);



    std::string create_client(const std::string& id_request,
                            const std::map<std::string, size_t>& args,
                            std::string& body);

private:
    ClientDataBase _db;
};

class PassHandlers {

public:
    PassHandlers() : _db() {};

    std::string all_passes(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string one_pass(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string delete_pass(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string insert_pass(const std::string& id_request, const std::map<std::string, size_t>& args);



    std::string create_pass(const std::string& id_request,
                            const std::map<std::string, size_t>& args,
                            std::string& body);

private:
    PassDataBase _db;
};

class CompanyHandlers {

public:
    CompanyHandlers() : _db() {};

    std::string all_companies(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string one_company(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string delete_company(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string insert_company(const std::string& id_request, const std::map<std::string, size_t>& args);



    std::string create_company(const std::string& id_request,
                            const std::map<std::string, size_t>& args,
                            std::string& body);

private:
    CompanyDataBase _db;
};

class PassageHandlers {

public:
    PassageHandlers() : _db() {};

    std::string all_cpassages(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string one_passage(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string delete_passage(const std::string& id_request, const std::map<std::string, size_t>& args);
    std::string insert_passage(const std::string& id_request, const std::map<std::string, size_t>& args);



    std::string create_passage(const std::string& id_request,
                            const std::map<std::string, size_t>& args,
                            std::string& body);

private:
    PassageDataBase _db;
};

#endif  // VISIONLIB_INCLUDE_ORM_HPP_
