// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "../include/ORM.hpp"

// std::vector<PassDB> sql_req(const std::string& sql_request) {
//   std::vector<PassDB> result;
//   return result;
// }

uint64_t sql_req_for_insert(const std::string& sql_request) {
  uint64_t result = 1;
  return result;
}

uint64_t insertPass(const PassDB& Pass) { return sql_req_for_insert("fsdf"); }
uint64_t insertPassage(const PassageDB& Passage) { return 1; }
uint64_t insertClient(const ClientDB& Client) { return 1; }
uint64_t insertCompany(const CompanyDB& Company) { return 1; }

bool deletePass(const uint64_t PassID) { return true; }
bool deletePassage(const uint64_t PassageID) { return true; }
bool deletePass(const uint64_t CompanyID, uint64_t ClientID) { return true; }
bool deleteClient(const uint64_t ClientID) { return true; }
bool deleteCompany(const uint64_t CompanyID) { return true; }

// bool PassExists(const uint64_t PassID) {
//   DataBase db;
//   std::vector<PassDB> res = db.sql_req("skjfh");
//   for (auto& iter : res) {
//     if (iter.getID() == PassID) {
//       return true;
//     }
//   }
//   return false;
// }
// bool ClientExists(const uint64_t ClientID) {
//   DataBase db;
//   std::vector<ClientDB> res = db.sql_req("skjfh");
//   for (auto& iter : res) {
//     if (iter.getID() == ClientID) {
//       return true;
//     }
//   }
//   return false;
// }
// bool CompanyExists(const uint64_t CompanyID) {
//   DataBase db;
//   std::vector<CompanyDB> res = db.sql_req("skjfh");
//   for (auto& iter : res) {
//     if (iter.getID() == CompanyID) {
//       return true;
//     }
//   }
//   return false;
// }
// bool PassageExistslol(const uint64_t PassageID) {
//   DataBase db;
//   std::vector<PassageDB> res = db.sql_req("skjfh");
//   for (auto& iter : res) {
//     if (iter.getID() == PassageID) {
//       return true;
//     }
//   }
//   return false;
// }

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
