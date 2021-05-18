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

DataBase::DataBase() {
  str_db_settings =
      "dbname=Monkeys host=localhost user=postgres password=password port=5432";
  try {
    database_ = std::make_unique<pqxx::connection>(str_db_settings);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "Connecting!" << std::endl;
}

DataBase::DataBase(std::map<std::string, std::string>& db_settings) {
  str_db_settings =
      ("dbname=" + db_settings["dbname"] + " host=" + db_settings["host"] +
       " user=" + db_settings["user"] + " password=" + db_settings["password"] +
       " port=5432");
  try {
    database_ = std::make_unique<pqxx::connection>(str_db_settings);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "Connecting!" << std::endl;
}


bool PassDataBase::deletePass(const uint64_t& PassID) {
  if (PassExists(PassID) == false) {
		std::cout << "Client does not exists" << std::endl;
		return false;
	}

  std::string sql_request = "select exists(select id from passage where passage.pass_id = (select id from pass where pass.id = '" + std::to_string(PassID) + "'))";
	pqxx::result r = do_select_request(sql_request);

	auto exist_flag = r[0][0].as<std::string>();
  if (exist_flag == "t") {
      std::cout << "Pass is linked to passage" << std::endl;
      return false;
  }

	sql_request = "delete from pass where pass.id = " + std::to_string(PassID);

	do_modifying_request(sql_request);

	std::cout << "Delete pass" << std::endl;

	return true;
}

bool PassageDataBase::deletePassage(const uint64_t& PassageID) {
  if (PassageExists(PassageID) == false) {
		std::cout << "Client does not exists" << std::endl;
		return false;
	}

	std::string sql_request = "delete from passage where passage.id = " + std::to_string(PassageID);

	do_modifying_request(sql_request);

	std::cout << "Delete passage" << std::endl;

	return true;
}

bool ClientDataBase::deleteCLient(const std::string& login) {
	if (ClientExists(login) == false) {
		std::cout << "Client does not exists" << std::endl;
		return false;
	}

	std::string sql_request = "select exists(select id from pass where pass.client_id = (select id from client where client.login = '" + login + "'))";
	pqxx::result r = do_select_request(sql_request);

	auto exist_flag = r[0][0].as<std::string>();
    if (exist_flag == "t") {
		    std::cout << "Client is linked to pass" << std::endl;
        return false;
    }

	sql_request = "delete from client where client.login = '" + login + "'";

	do_modifying_request(sql_request);

	std::cout << "Delete client" << std::endl;

	return true;
}
bool CompanyDataBase::deleteCompany(const std::string& name) {
  if (CompanyExists(name) == false) {
		std::cout << "Company does not exists" << std::endl;
		return false;
	}

	std::string sql_request = "select exists(select id from pass where pass.company_id = (select id from company where company.company_name = '" + name + "'))";
	pqxx::result r = do_select_request(sql_request);

	auto exist_flag = r[0][0].as<std::string>();
    if (exist_flag == "t") {
		    std::cout << "Company is linked to pass" << std::endl;
        return false;
    }

	sql_request = "delete from company where company.company_name = '" + name + "'";

	do_modifying_request(sql_request);

	std::cout << "Delete comapny" << std::endl;

	return true;
}

uint64_t ClientDataBase::insertClient(const std::string& Login, const std::string& Email, const std::string& Password) {
	if (ClientExists(Login) == true) return false;

  	std::string sql_request = "insert into client(login, email, password) values ('" + Login + "', '"
			   + Email + "', '"
			   + Password + "')";

  do_modifying_request(sql_request);

	std::cout << "Insert client" << std::endl;

  std::string sql_req_for_post_id = "select max(id) from client";
  pqxx::result r = do_select_request(sql_req_for_post_id);
  auto client_id = r[0][0].as<uint64_t>();

  return client_id;
}

uint64_t CompanyDataBase::insertCompany(const std::string& name) {
  if (CompanyExists(name) == true) return false;

  	std::string sql_request = "insert into company(company_name) values ('" + name + "')";

  do_modifying_request(sql_request);

	std::cout << "Insert company" << std::endl;

  std::string sql_req_for_post_id = "select max(id) from company";
  pqxx::result r = do_select_request(sql_req_for_post_id);
  auto company_id = r[0][0].as<uint64_t>();

  return company_id;
}

uint64_t PassDataBase::insertPass(const std::string& private_key, const uint64_t& CompanyID, const uint64_t& ClientID) {
  
  auto exist_sql_req = "select exists(select id from pass where pass.private_key = '" + private_key + "')";
  pqxx::result exist = do_select_request(exist_sql_req);
  auto exist_flag = exist[0][0].as<std::string>();
  if (exist_flag == "t") {
      std::cout << "This private key already exists" << std::endl;
      return false;
  }

  exist_sql_req = "select exists(select id from client where client.id = '" + std::to_string(ClientID) + "')";
  exist = do_select_request(exist_sql_req);
  exist_flag = exist[0][0].as<std::string>();
  if (exist_flag != "t") {
    std::cout << "This client does not exists for linked" << std::endl;
    return false;
  }

  exist_sql_req = "select exists(select id from company where company.id = '" + std::to_string(CompanyID) + "')";
  exist = do_select_request(exist_sql_req);
  exist_flag = exist[0][0].as<std::string>();
  if (exist_flag != "t") {
    std::cout << "This company does not exists for linked" << std::endl;
    return false;
  }

  std::string sql_request = "insert into pass(private_key, company_id, client_id) values ('" 
  + private_key + "', '" 
  + std::to_string(CompanyID) + "', '" 
  + std::to_string(ClientID) + "')";

  do_modifying_request(sql_request);

	std::cout << "Insert pass" << std::endl;

  std::string sql_req_for_post_id = "select max(id) from pass";
  pqxx::result r = do_select_request(sql_req_for_post_id);
  auto pass_id = r[0][0].as<uint64_t>();

  return pass_id;
}


bool PassDataBase::PassExists(const uint64_t& PassID) {
  auto exist_sql_req = ("select exists(select id from pass where pass.id = '" + std::to_string(PassID) + "')");
  pqxx::result exist = do_select_request(exist_sql_req);
  auto exist_flag = exist[0][0].as<std::string>();
  if (exist_flag == "t") {
      return true;
  } else {
      return false;
  }
}

bool ClientDataBase::ClientExists(const std::string& login) {
  auto exist_sql_req =
      ("select exists(select id from client where client.login = '" + login +
       "')");
  pqxx::result exist = do_select_request(exist_sql_req);
  auto exist_flag = exist[0][0].as<std::string>();
  if (exist_flag == "t") {
    return true;
  } else {
    return false;
  }
}

bool ClientDataBase::ClientExists(const uint64_t& ClientID) {
  auto exist_sql_req =
      ("select exists(select id from client where client.id = '" + std::to_string(ClientID) +
       "')");
  pqxx::result exist = do_select_request(exist_sql_req);
  auto exist_flag = exist[0][0].as<std::string>();
  if (exist_flag == "t") {
    return true;
  } else {
    return false;
  }
}

bool CompanyDataBase::CompanyExists(const std::string& name) {
  auto exist_sql_req = "select exists(select id from company where company.company_name = '" + name + "')";
  pqxx::result exist = do_select_request(exist_sql_req);
  auto exist_flag = exist[0][0].as<std::string>();
  if (exist_flag == "t") {
    return true;
  } else {
    return false;
  }
}

bool PassageDataBase::PassageExists(const uint64_t& PassageID) {
  auto exist_sql_req =
      ("select exists(select id from passage where passage.id = '" + std::to_string(PassageID) +
       "')");
  pqxx::result exist = do_select_request(exist_sql_req);
  auto exist_flag = exist[0][0].as<std::string>();
  if (exist_flag == "t") {
    return true;
  } else {
    return false;
  }
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

std::vector<PassDB> PassDataBase::getClientsPasses(const uint64_t& ClientID) {
  std::vector<PassDB> result;
  
  auto exist_sql_req = ("select exists(select id from pass where pass.client_id = '" + std::to_string(ClientID) + "')");
  pqxx::result exist = do_select_request(exist_sql_req);
  auto exist_flag = exist[0][0].as<std::string>();
  if (exist_flag == "f") {
      std::cout << "No passes for this client" << std::endl;
      return result;
  }


  std::string sql_request = "select * from pass where pass.client_id = " + std::to_string(ClientID);
  pqxx::result r = do_select_request(sql_request);

  for (const auto& row: r) {
      PassDB temp(
              row[0].as<uint64_t>(),
              row[3].as<std::string>(),
              row[2].as<uint64_t>(),
              row[1].as<uint64_t>());
      result.push_back(temp);
  }
  return result;
}

std::vector<PassDB> PassDataBase::getCompanysPasses(const uint64_t& CompanyID) {
  std::vector<PassDB> passes(0);
  return passes;
}

std::vector<PassageDB> getPassesPassages(const uint64_t PassID) {
  std::vector<PassageDB> passes(0);
  return passes;
}

PassDB PassDataBase::getPass(const uint64_t& PassID) {
	std::string sql_request = "select * from pass where pass.id = " + std::to_string(PassID);
  pqxx::result r = do_select_request(sql_request);

	const auto& row = r.at(0);
  PassDB result(
    row[0].as<uint64_t>(),
    row[3].as<std::string>(),
    row[2].as<uint64_t>(),
    row[1].as<uint64_t>());
  return result; 
}

// PassageDB PassageDataBase::getPassage(const uint64_t PassageID) {
//   std::string sql_request = "select * from passage where passage.id = " + std::to_string(PassageID);
//   pqxx::result r = do_select_request(sql_request);

// 	const auto& row = r.at(0);
//   PassageDB result(
//     row[0].as<uint64_t>(),
//     row[3].as<time_t>(),
//     row[2].as<uint8_t>(),
//     row[1].as<uint64_t>());
//   return result; 
// }

ClientDB ClientDataBase::getClient(const std::string login) {
  std::string sql_request =
      "select * from client where client.login = '" + login + "'";
  pqxx::result r = do_select_request(sql_request);

	const auto& row = r.at(0);
  ClientDB result(
    row[0].as<uint64_t>(),
    row[1].as<std::string>(),
    row[2].as<std::string>(),
    row[3].as<std::string>());
  return result; 
}
CompanyDB CompanyDataBase::getCompany(const uint64_t& CompanyID) {
  std::string sql_request =
      "select * from company where company.id = '" + std::to_string(CompanyID) + "'";
  pqxx::result r = do_select_request(sql_request);

	const auto& row = r.at(0);
  CompanyDB result(
    row[0].as<uint64_t>(),
    row[1].as<std::string>());
  return result; 
}

ClientDataBase::ClientDataBase(std::map<std::string, std::string>& db_settings)
    : DataBase(db_settings) {}

PassDataBase::PassDataBase(std::map<std::string, std::string>& db_settings)
    : DataBase(db_settings) {}

CompanyDataBase::CompanyDataBase(
    std::map<std::string, std::string>& db_settings)
    : DataBase(db_settings) {}

PassageDataBase::PassageDataBase(std::map<std::string, std::string>& db_settings) 
    : DataBase(db_settings){ }

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
