// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "../include/ORM.hpp"

uint64_t insertPass(const PassDB& Pass) { return 1; }
uint64_t insertPassage(const PassageDB& Passage) { return 1; }
uint64_t insertClient(const ClientDB& Client) { return 1; }
uint64_t insertCompany(const CompanyDB& Company) { return 1; }

bool deletePass(const uint64_t PassID) { return true; }
bool deletePassage(const uint64_t PassageID) { return true; }
bool deletePass(const uint64_t CompanyID, uint64_t ClientID) { return true; }
bool deleteClient(const uint64_t ClientID) { return true; }
bool deleteCompany(const uint64_t CompanyID) { return true; }

bool PassExists(const uint64_t PassID) { return true; }
bool ClientExists(const uint64_t ClientID) { return true; }
bool CompanyExists(const uint64_t CompanyID) { return true; }
bool PassageExists(const uint64_t PassageID) { return true; }

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

template <class T>
std::vector<T> do_select_request(const std::string& sql_request) {
  std::vector<T> request;
  return request;
}
