// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "database.hpp"


bool DataBase::is_opened() const {
	if (database_->is_open()) {
		return true;
	}
	return false;
}

DataBase::DataBase()  {
	str_db_settings = "dbname=Monkeys host=localhost user=postgres password=password port=5432";
	try {
		database_ = std::make_unique<pqxx::connection>(str_db_settings);
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Connecting!" << std::endl;
}

DataBase::DataBase(std::map<std::string, std::string> &db_settings)  {
	str_db_settings = ("dbname=" + db_settings["dbname"] +
							  " host=" + db_settings["host"] +" user=" + db_settings["user"] +
							  " password=" + db_settings["password"] + " port=5432");
	try {
		database_ = std::make_unique<pqxx::connection>(str_db_settings);
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Connecting!" << std::endl;
}

void ClientDataBase::do_modifying_request(std::string& sql_request) {
	pqxx::connection con(str_db_settings);
	pqxx::work W(con);
	W.exec(sql_request);
	W.commit();
}

void PassDataBase::do_modifying_request(std::string& sql_request) {
	pqxx::connection con(str_db_settings);
	pqxx::work W(con);
	W.exec(sql_request);
	W.commit();
}

void CompanyDataBase::do_modifying_request(std::string& sql_request) {
	pqxx::connection con(str_db_settings);
	pqxx::work W(con);
	W.exec(sql_request);
	W.commit();
}

void PassageDataBase::do_modifying_request(std::string& sql_request) {
	pqxx::connection con(str_db_settings);
	pqxx::work W(con);
	W.exec(sql_request);
	W.commit();
}

pqxx::result ClientDataBase::do_select_request(std::string& sql_request) {
	pqxx::connection con(str_db_settings);
	pqxx::work N(con);
	pqxx::result R = N.exec(sql_request);
	N.commit();
	return R;
}

pqxx::result PassDataBase::do_select_request(std::string& sql_request) {
	pqxx::connection con(str_db_settings);
	pqxx::work N(con);
	pqxx::result R = N.exec(sql_request);
	N.commit();
	return R;
}

pqxx::result CompanyDataBase::do_select_request(std::string& sql_request) {
	pqxx::connection con(str_db_settings);
	pqxx::work N(con);
	pqxx::result R = N.exec(sql_request);
	N.commit();
	return R;
}

pqxx::result PassageDataBase::do_select_request(std::string& sql_request) {
	pqxx::connection con(str_db_settings);
	pqxx::work N(con);
	pqxx::result R = N.exec(sql_request);
	N.commit();
	return R;
}


bool PassDataBase::deletePass(const uint64_t& PassID) { return true; }
bool PassageDataBase::deletePassage(const uint64_t& PassageID) { return true; }
bool ClientDataBase::deleteCLient(const uint64_t ClientID) { return true; }
bool CompanyDataBase::deleteCompany(const uint64_t CompanyID) { return true; }

bool ClientDataBase::insertClient(const std::string& Login, const std::string& Email, const std::string& Password) {
  	std::string sql_request = "insert into client(login, email, password) values ('" + Login + "', '"
			   + Email + "', '"
			   + Password + "')";

	do_modifying_request(sql_request);

	std::cout << "Add client" << std::endl;

	return true;
}

bool PassDataBase::PassExists(const uint64_t PassID) {
  auto exist_sql_req = ("select exists(select id from client where pass.if = '" + std::to_string(PassID) + "')");
    pqxx::result exist = do_select_request(exist_sql_req);
    auto exist_flag = exist[0][0].as<std::string>();
    if (exist_flag == "t") {
        return true;
    } else {
        return false;
    }
}

bool ClientDataBase::ClientExists(const std::string& login) {
    auto exist_sql_req = ("select exists(select id from client where client.login = '" + login + "')");
    pqxx::result exist = do_select_request(exist_sql_req);
    auto exist_flag = exist[0][0].as<std::string>();
    if (exist_flag == "t") {
        return true;
    } else {
        return false;
    }
}

bool CompanyDataBase::CompanyExists(const std::string& name) {
  auto exist_sql_req = ("select exists(select id from client where client.login = '" + name + "')");
    pqxx::result exist = do_select_request(exist_sql_req);
    auto exist_flag = exist[0][0].as<std::string>();
    if (exist_flag == "t") {
        return true;
    } else {
        return false;
    }
}

bool PassageDataBase::PassageExists(const uint64_t& PassageID) {
  std::vector<PassageDB> res;
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

std::vector<PassageDB> PassageDataBase::getAllPassages(const std::string& sql_limit,
                                                       const std::string& sql_offset) {
  std::vector<PassageDB> passes(0);
  return passes;
}

std::vector<ClientDB> ClientDataBase::getAllClients(const std::string& sql_limit,
                                                    const std::string& sql_offset) {
  std::vector<ClientDB> passes(0);
  return passes;
}

std::vector<CompanyDB> CompanyDataBase::getAllCompanys(const std::string& sql_limit,
                                                       const std::string& sql_offset) {
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

ClientDB ClientDataBase::getClient(const std::string login) { 
	std::string sql_request = "select * from client where client.login = '" + login + "'";
    pqxx::result r = do_select_request(sql_request);

	const auto& row = r.at(0);
    ClientDB result(
			row[0].as<int>(),
			row[1].as<std::string>(),
			row[2].as<std::string>(),
			row[3].as<std::string>());
    return result; 
}
CompanyDB getCompany(const uint64_t CompanyID) { return CompanyDB(); }

ClientDataBase::ClientDataBase(std::map<std::string, std::string>& db_settings) : DataBase(db_settings){ }

PassDataBase::PassDataBase(std::map<std::string, std::string>& db_settings) : DataBase(db_settings){ }

CompanyDataBase::CompanyDataBase(std::map<std::string, std::string>& db_settings) : DataBase(db_settings){ }

PassageDataBase::PassageDataBase(std::map<std::string, std::string>& db_settings) : DataBase(db_settings){ }
