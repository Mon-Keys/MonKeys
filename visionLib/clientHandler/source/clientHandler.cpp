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
  boost::property_tree::ptree confData;
  if (!exist) {
    std::ofstream ofs("server_auth.json");
    ofs.close();
  }

  if (_Cldb.ClientExists(Login) == false) {
    tree.put("login", Login);
    tree.put("status", "Not Exists");
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
    tree.put("status", "Incorrect password");
    boost::property_tree::write_json("server_auth.json", tree);
    return "server_auth.json";
  }
}
std::string clientHandler::logOutClient(uint64_t ClientID) { return ""; }
std::string clientHandler::registerClient(const std::string& Login,
                                          const std::string& Email,
                                          const std::string& Password) {
  boost::property_tree::ptree tree;

  bool exist = existsClient("server_reg.json");
  boost::property_tree::ptree confData;
  if (!exist) {
    std::ofstream ofs("server_reg.json");
    ofs.close();
  }

  tree.put("login", Login);
  if (_Cldb.ClientExists(Login) == true) {
    tree.put("status", "Already exists");
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

std::string clientHandler::getTimeCode(const std::string& Login, const std::string& Password) {
  boost::property_tree::ptree tree;

  bool exist = existsClient("server_time.json");
  boost::property_tree::ptree confData;
  if (!exist) {
    std::ofstream ofs("server_time.json");
    ofs.close();
  }

  if (_Cldb.ClientExists(Login) == false) {
    tree.put("login", Login);
    tree.put("status", "Not Exists");
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
      tree.put("passes", "No passes");
    } else {
      boost::property_tree::ptree children;
      for (int i = 0; i < passes_vec.size(); i++) {
        boost::property_tree::ptree child;
        child.put("passID", std::to_string(passes_vec[i].getID()));
        child.put("privateKey", passes_vec[i].getprivate());
        child.put("companyID", std::to_string(passes_vec[i].getCompanyID()));
        TimeCodeGenerator generator(passes_vec[i].getprivate(), passes_vec[i].getID(), passes_vec[i].getCompanyID(), 30);
        std::vector<std::string> str_vec = generator.generateTimeCodesAhead(5);
        for (int i = 0; i < str_vec.size(); i++) {
          child.put(std::to_string(i + 1), str_vec[i]);
        }
        children.push_back(std::make_pair("", child));
      }
      tree.add_child("passes", children);
    }
    boost::property_tree::write_json("server_time.json", tree);
    return "server_time.json";
  } else {
    tree.put("login", Login);
    tree.put("status", "Incorrect password");
    boost::property_tree::write_json("server_time.json", tree);
    return "server_time.json";
  }
}
