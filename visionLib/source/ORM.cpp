// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "../include/ORM.hpp"

bool insertPass(PassDB& PassID) {
    return true;
}
bool insertPassage(PassageDB& PassageID){
    return true;
}
bool insertClient(ClientDB& ClientID){
    return true
}

bool insertCompany(CompanyDB& CompanyID){
    return true;
}


bool deletePass(uint64_t PassID){
    return true;
}

bool deletePassage(uint64_t PassageID){
    return true;
}

bool deletePass(uint64_t CompanyID, uint64_t ClientID){
    return true;
}

bool deleteClient(uint64_t ClientID){
    return true;
}

bool deleteCompany(uint64_t CompanyID){
    return true;
}

bool PassExists(uint64_t PassID){
    return true;
}

bool ClientExists(uint64_t ClientID){
    return true;
}

bool CompanyExists(uint64_t CompanyID){
    return true;
}

bool PassageExists(uint64_t PassageID){
    return true;
}

std::vector<PassDB> getAllPasses(const std::string& sql_limit, const std::string& sql_offset){
    std::vector<PassDB> passes(0);
    return passes;
}

std::vector<PassageDB> getAllPassages(const std::string& sql_limit, const std::string& sql_offset){
    std::vector<PassageDB> passes(0);
    return passes;
}

std::vector<ClientDB> getAllClients(const std::string& sql_limit, const std::string& sql_offset){
    std::vector<ClientDB> passes(0);
}

std::vector<CompanyDB> getAllCompanys(const std::string& sql_limit, const std::string& sql_offset){
    std::vector<CompanyDB> passes(0);
}

std::vector<PassDB> getClientsPasses(const uint64_t ClientID){
    std::vector<PassDB> passes(0);
}

std::vector<PassDB> getCompanysPasses(const uint64_t CompanyID){
    std::vector<PassDB> passes(0);
}

std::vector<PassageDB> getPassesPassages(const uint64_t PassID){
    std::vector<PassageDB> passes(0);
}



PassDB getPass(std::string PassID){

}

PassDB getPassage(std::string PassageID){

}

ClientDB getClient(std::string ClientID){

}

CompanyDB getCompany(std::string CompanyID){

}
