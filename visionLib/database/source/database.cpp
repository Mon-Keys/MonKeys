// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "database.hpp"

std::vector<PassDB> PassDataBase::sqlReq(const std::string& sql_request) {
  std::vector<PassDB> result;
  return result;
}

std::vector<ClientDB> ClientDataBase::sqlReq(const std::string& sql_request) {
  std::vector<ClientDB> result;
  return result;
}

std::vector<PassageDB> PassageDataBase::sqlReq(const std::string& sql_request) {
  std::vector<PassageDB> result;
  return result;
}

std::vector<CompanyDB> CompanyDataBase::sqlReq(const std::string& sql_request) {
  std::vector<CompanyDB> result;
  return result;
}

uint64_t DataBase::sql_req_for_insert(const std::string& sql_request) {
  uint64_t result = 1;
  return result;
}

uint64_t PassDataBase::insertPass(const PassDB& Pass) {
  return sql_req_for_insert("fsdf");
}
uint64_t PassageDataBase::insertPassage(const PassageDB& Passage) {
  return sql_req_for_insert("fsdf");
}
uint64_t ClientDataBase::insertClient(const ClientDB& Client) {
  return sql_req_for_insert("fsdf");
}
uint64_t CompanyDataBase::insertCompany(const CompanyDB& Company) {
  return sql_req_for_insert("fsdf");
}

bool PassDataBase::deletePass(const uint64_t PassID) { return true; }
bool PassageDataBase::deletePassage(const uint64_t PassageID) { return true; }
bool ClientDataBase::deleteCLient(const uint64_t ClientID) { return true; }
bool CompanyDataBase::deleteCompany(const uint64_t CompanyID) { return true; }

bool PassDataBase::PassExists(const uint64_t PassID) {
  std::vector<PassDB> res = PassDataBase::sqlReq("skjfh");
  // std::vector<PassDB> res;
  // for (int i = 1; i < 3; i++) {
  //   PassDB pass;
  //   pass.setClientID(i);
  //   pass.setID(i);
  //   pass.setprivate(STR);
  //   pass.setCompanyID(i);
  //   res.push_back(pass);
  // }
  for (int i = 0; i < res.size(); i++) {
    if (res[i].getID() == PassID) {
      return true;
    }
  }
  return false;
}

bool ClientDataBase::ClientExists(const uint64_t ClientID) {
  std::vector<ClientDB> res = ClientDataBase::sqlReq("skjfh");
  // std::vector<ClientDB> res;
  // for (int i = 0; i < 3; i++) {
  //   ClientDB client;
  //   client.setID(i);
  //   client.setLogin("login");
  //   client.setPassword("password");
  //   client.setEmail("inagdimaev@mail.ru");
  //   res.push_back(client);
  // }
  for (int i = 0; i < res.size(); i++) {
    if (res[i].getID() == ClientID) {
      return true;
    }
  }
  return false;
}

bool CompanyDataBase::CompanyExists(const uint64_t CompanyID) {
  std::vector<CompanyDB> res = CompanyDataBase::sqlReq("skjfh");
  // std::vector<CompanyID> res;
  // for (int i = 0; i < 3; i++) {
  //   CompanyDB company;
  //   company.setID(i);
  //   company.setName("sdgds");
  //   res.push_back(company);
  // }
  for (int i = 0; i < res.size(); i++) {
    if (res[i].getID() == CompanyID) {
      return true;
    }
  }
  return false;
}

bool PassageDataBase::PassageExists(const uint64_t PassageID) {
  std::vector<PassageDB> res = PassageDataBase::sqlReq("skjfh");
  // std::vector<PassageID> res;
  // for (int i = 0; i < 3; i++) {
  //   PassageDB passage;
  //   passage.setID(i);
  //   passage.setActionType(0);
  //   passage.setTime(time_now);
  //   passage.setPassID(i);
  //   res.push_back(passage);
  // }
  for (int i = 0; i < res.size(); i++) {
    if (res[i].getID() == PassageID) {
      return true;
    }
  }
  return false;
}

std::vector<PassDB> PassDataBase::getAllPasses(const std::string& sql_limit,
                                               const std::string& sql_offset) {
  std::vector<PassDB> passes(0);
  return passes;
}

std::vector<PassageDB> PassageDataBase::getAllPassages(
    const std::string& sql_limit, const std::string& sql_offset) {
  std::vector<PassageDB> passes(0);
  return passes;
}

std::vector<ClientDB> ClientDataBase::getAllClients(
    const std::string& sql_limit, const std::string& sql_offset) {
  std::vector<ClientDB> passes(0);
  return passes;
}

std::vector<CompanyDB> CompanyDataBase::getAllCompanys(
    const std::string& sql_limit, const std::string& sql_offset) {
  std::vector<CompanyDB> passes(0);
  return passes;
}

std::vector<PassDB> PassDataBase::getClientsPasses(const uint64_t ClientID) {
  std::vector<PassDB> passes(0);
  return passes;
}

std::vector<PassDB> PassDataBase::getCompanysPasses(const uint64_t CompanyID) {
  std::vector<PassDB> passes(0);
  return passes;
}

std::vector<PassageDB> getPassesPassages(const uint64_t PassID) {
  std::vector<PassageDB> passes(0);
  return passes;
}

PassDB PassDataBase::getPass(const uint64_t PassID) { return PassDB(); }
PassageDB PassageDataBase::getPassage(const uint64_t PassageID) {
  return PassageDB();
}
ClientDB getClient(const uint64_t ClientID) { return ClientDB(); }
CompanyDB getCompany(const uint64_t CompanyID) { return CompanyDB(); }
