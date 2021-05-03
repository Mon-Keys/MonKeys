// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "../include/ORM.hpp"

std::vector<PassDB> DataBase::sqlReqForPass(const std::string& sql_request) {
  std::vector<PassDB> result;
  return result;
}

std::vector<ClientDB> DataBase::sqlReqForClient(
    const std::string& sql_request) {
  std::vector<ClientDB> result;
  return result;
}

std::vector<PassageDB> DataBase::sqlReqForPassage(
    const std::string& sql_request) {
  std::vector<PassageDB> result;
  return result;
}

std::vector<CompanyDB> DataBase::sqlReqForCompany(
    const std::string& sql_request) {
  std::vector<CompanyDB> result;
  return result;
}

uint64_t DataBase::sql_req_for_insert(const std::string& sql_request) {
  uint64_t result = 1;
  return result;
}

uint64_t DataBase::insertPass(const PassDB& Pass) {
  return sql_req_for_insert("fsdf");
}
uint64_t DataBase::insertPassage(const PassageDB& Passage) {
  return sql_req_for_insert("fsdf");
}
uint64_t DataBase::insertClient(const ClientDB& Client) {
  return sql_req_for_insert("fsdf");
}
uint64_t DataBase::insertCompany(const CompanyDB& Company) {
  return sql_req_for_insert("fsdf");
}

bool DataBase::deletePass(const uint64_t PassID) { return true; }
bool DataBase::deletePassage(const uint64_t PassageID) { return true; }
bool DataBase::deletePass(const uint64_t CompanyID, uint64_t ClientID) {
  return true;
}
bool DataBase::deleteClient(const uint64_t ClientID) { return true; }
bool DataBase::deleteCompany(const uint64_t CompanyID) { return true; }

bool DataBase::PassExists(const uint64_t PassID) {
  DataBase db;
  std::vector<PassDB> res = db.sqlReqForPass("skjfh");
  for (auto& iter : res) {
    if (iter.getID() == PassID) {
      return true;
    }
  }
  return false;
}
bool DataBase::ClientExists(const uint64_t ClientID) {
  DataBase db;
  std::vector<ClientDB> res = db.sqlReqForClient("skjfh");
  for (auto& iter : res) {
    if (iter.getID() == ClientID) {
      return true;
    }
  }
  return false;
}
bool DataBase::CompanyExists(const uint64_t CompanyID) {
  DataBase db;
  std::vector<CompanyDB> res = db.sqlReqForCompany("skjfh");
  for (auto& iter : res) {
    if (iter.getID() == CompanyID) {
      return true;
    }
  }
  return false;
}
bool DataBase::PassageExists(const uint64_t PassageID) {
  DataBase db;
  std::vector<PassageDB> res = db.sqlReqForPassage("skjfh");
  for (auto& iter : res) {
    if (iter.getID() == PassageID) {
      return true;
    }
  }
  return false;
}

std::vector<PassDB> getAllPasses(const std::string& sql_limit,
                                 const std::string& sql_offset) {
  std::vector<PassDB> passes(0);
  return passes;
}

std::vector<PassageDB> getAllPassages(const std::string& sql_limit,
                                      const std::string& sql_offset) {
  std::vector<PassageDB> passes(0);
  return passes;
}

std::vector<ClientDB> getAllClients(const std::string& sql_limit,
                                    const std::string& sql_offset) {
  std::vector<ClientDB> passes(0);
  return passes;
}

std::vector<CompanyDB> getAllCompanys(const std::string& sql_limit,
                                      const std::string& sql_offset) {
  std::vector<CompanyDB> passes(0);
  return passes;
}

std::vector<PassDB> getClientsPasses(const uint64_t ClientID) {
  std::vector<PassDB> passes(0);
  return passes;
}

std::vector<PassDB> getCompanysPasses(const uint64_t CompanyID) {
  std::vector<PassDB> passes(0);
  return passes;
}

std::vector<PassageDB> getPassesPassages(const uint64_t PassID) {
  std::vector<PassageDB> passes(0);
  return passes;
}

PassDB getPass(const uint64_t PassID) { return PassDB(); }
PassageDB getPassage(const uint64_t PassageID) { return PassageDB(); }
ClientDB getClient(const uint64_t ClientID) { return ClientDB(); }
CompanyDB getCompany(const uint64_t CompanyID) { return CompanyDB(); }
