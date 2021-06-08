// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//

#include "clientHandler.hpp"

#include "TimeCodeGenerator.hpp"
#include "database.hpp"

bool existsClient(const std::string& name) {
  struct stat buffer;
  return (stat(name.c_str(), &buffer) == 0);
}

std::string clientHandler::logInClient(const std::string& Login,
                                       const std::string& Password) {
  boost::property_tree::ptree tree;

  bool exist = existsClient("server_auth.json");
  if (!exist) {
    std::ofstream ofs("server_auth.json");
    ofs.close();
  }

  if (_Cldb.ClientExists(Login) == false) {
    tree.put("login", Login);
    tree.put("status", "not_exists");
    boost::property_tree::write_json("server_auth.json", tree);
    return "server_auth.json";
  }

  ClientDB client = _Cldb.getClient(Login);

  if (client.getPassword() == Password) {
    tree.put("ID", std::to_string(client.getID()));
    tree.put("login", client.getLogin());
    tree.put("email", client.getEmail());
    tree.put("status", "success");
    boost::property_tree::write_json("server_auth.json", tree);
    return "server_auth.json";
  } else {
    tree.put("login", Login);
    tree.put("status", "incorrect_password");
    boost::property_tree::write_json("server_auth.json", tree);
    return "server_auth.json";
  }
}
std::string clientHandler::registerClient(const std::string& Login,
                                          const std::string& Email,
                                          const std::string& Password) {
  boost::property_tree::ptree tree;

  bool exist = existsClient("server_reg.json");
  if (!exist) {
    std::ofstream ofs("server_reg.json");
    ofs.close();
  }

  tree.put("login", Login);
  if (_Cldb.ClientExists(Login) == true) {
    tree.put("status", "already_exists");
    boost::property_tree::write_json("server_reg.json", tree);
    return "server_reg.json";
  }

  uint64_t client_id = _Cldb.insertClient(Login, Email, Password);
  ClientDB client = _Cldb.getClient(Login);
  tree.put("ID", std::to_string(client_id));
  tree.put("login", client.getLogin());
  tree.put("email", client.getEmail());
  tree.put("password", client.getPassword());
  tree.put("status", "success");
  boost::property_tree::write_json("server_reg.json", tree);
  return "server_reg.json";
}

std::string clientHandler::getTimeCode(const std::string& Login,
                                       const std::string& Password) {
  boost::property_tree::ptree tree;

  bool exist = existsClient("server_time.json");
  if (!exist) {
    std::ofstream ofs("server_time.json");
    ofs.close();
  }

  if (_Cldb.ClientExists(Login) == false) {
    tree.put("login", Login);
    tree.put("status", "not_exists");
    boost::property_tree::write_json("server_time.json", tree);
    return "server_time.json";
  }

  ClientDB client = _Cldb.getClient(Login);

  if (client.getPassword() == Password) {
    tree.put("status", "success");
    tree.put("ID", std::to_string(client.getID()));
    tree.put("login", client.getLogin());
    tree.put("email", client.getEmail());
    tree.put("password", client.getPassword());

    std::vector<PassDB> passes_vec = _Passdb.getClientsPasses(client.getID());

    if (passes_vec.empty()) {
      tree.put("passes", "no_passes");
    } else {
      boost::property_tree::ptree children;
      for (int i = 0; i < passes_vec.size(); i++) {
        boost::property_tree::ptree child;
        child.put("passID", std::to_string(passes_vec[i].getID()));
        child.put("privateKey", passes_vec[i].getprivate());
        child.put("companyID", std::to_string(passes_vec[i].getCompanyID()));

        CompanyDB company = _Codb.getCompany(passes_vec[i].getCompanyID());

        child.put("companyName", company.getName());

        TimeCodeGenerator generator(passes_vec[i].getprivate(),
                                    passes_vec[i].getID(),
                                    passes_vec[i].getCompanyID(), 30);
        std::string str_vec = generator.generateTimeCode();
        child.put("timecode", str_vec);

        children.push_back(std::make_pair("", child));
      }
      tree.add_child("passes", children);
    }
    boost::property_tree::write_json("server_time.json", tree);
    return "server_time.json";
  } else {
    tree.put("login", Login);
    tree.put("status", "incorrect_password");
    boost::property_tree::write_json("server_time.json", tree);
    return "server_time.json";
  }
}

std::string clientHandler::logInAdmin(const std::string& CompanyName,
                                      const std::string& LecenseKey) {
  boost::property_tree::ptree tree;

  bool exist = existsClient("server_admin_auth.json");
  if (!exist) {
    std::ofstream ofs("server_admin_auth.json");
    ofs.close();
  }

  if (_Codb.CompanyExists(CompanyName) == false) {
    tree.put("company_name", CompanyName);
    tree.put("status", "not_exists");
    boost::property_tree::write_json("server_admin_auth.json", tree);
    return "server_admin_auth.json";
  }

  CompanyDB company = _Codb.getCompany(CompanyName);

  if (company.getLicenseKey() == LecenseKey) {
    tree.put("ID", std::to_string(company.getID()));
    tree.put("company_name", company.getName());
    tree.put("license_key", company.getLicenseKey());
    tree.put("status", "success");
    boost::property_tree::write_json("server_admin_auth.json", tree);
    return "server_admin_auth.json";
  } else {
    tree.put("company_name", CompanyName);
    tree.put("status", "incorrect_license_key");
    boost::property_tree::write_json("server_admin_auth.json", tree);
    return "server_admin_auth.json";
  }
}

std::string clientHandler::addCleintsPass(const std::string& Login,
                                          const std::string& Name) {
  boost::property_tree::ptree tree;

  bool exist = existsClient("server_add_pass.json");
  if (!exist) {
    std::ofstream ofs("server_add_pass.json");
    ofs.close();
  }

  if (!(_Cldb.ClientExists(Login))) {
    tree.put("status", "not_exists_client");
    boost::property_tree::write_json("server_add_pass.json", tree);
    return "server_add_pass.json";
  }

  if (!(_Codb.CompanyExists(Name))) {
    tree.put("status", "not_exists_company");
    boost::property_tree::write_json("server_add_pass.json", tree);
    return "server_add_pass.json";
  }

  ClientDB client = _Cldb.getClient(Login);

  CompanyDB company = _Codb.getCompany(Name);

  if (_Passdb.PassExists(client.getID(), company.getID())) {
    tree.put("status", "already_exists");
    boost::property_tree::write_json("server_add_pass.json", tree);
    return "server_add_pass.json";
  }

  srand(time(NULL));

  char let[17] = "0123456789ABCDEF";

  std::string str = "";

  for (int i = 0; i < 40; ++i) str += let[rand() % 16];

  uint64_t pass_id = _Passdb.insertPass(str, company.getID(), client.getID());

  tree.put("pass_id", std::to_string(pass_id));
  tree.put("private_key", str);
  tree.put("client_id", std::to_string(client.getID()));
  tree.put("company_id", std::to_string(company.getID()));
  tree.put("status", "success");
  boost::property_tree::write_json("server_add_pass.json", tree);

  return "server_add_pass.json";
}
