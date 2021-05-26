// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "terminalHandler.hpp"

#include <string>

#include "TimeCodeGenerator.hpp"

bool existsTerminal(const std::string& name) {
  struct stat buffer;
  return (stat(name.c_str(), &buffer) == 0);
}

std::string TerminalHandler::compareTimeCode(const std::string& timeCode,
                                             const std::string& Name,
                                             const std::string& Key) {
  boost::property_tree::ptree tree;

  bool exist = existsTerminal("terminal_server_compare.json");
  if (!exist) {
    std::ofstream ofs("terminal_server_compare.json");
    ofs.close();
  }

  if (_Codb.CompanyExists(Name) == false) {
    tree.put("company_name", Name);
    tree.put("status", "not_exists");
    boost::property_tree::write_json("terminal_server_compare.json", tree);
    return "terminal_server_compare.json";
  }

  CompanyDB company = _Codb.getCompany(Name);

  if (company.getLicenseKey() != Key) {
    tree.put("company_name", Name);
    tree.put("status", "incorrect_license_key");
    boost::property_tree::write_json("terminal_server_compare.json", tree);
    return "terminal_server_compare.json";
  }

  TimeCode tc(timeCode);

  uint64_t company_id = 0;
  uint64_t pass_id = 0;

  if (tc.isValid()) {
    company_id = tc.getCompanyID();
    pass_id = tc.getPassID();
  }

  if (company_id != company.getID()) {
    tree.put("verification", "error_novalid_terminal");
    boost::property_tree::write_json("terminal_server_compare.json", tree);
    return "terminal_server_compare.json";
  }

  if (!(_Passdb.PassExists(pass_id))) {
    tree.put("verification", "pass_not_exists");
    boost::property_tree::write_json("terminal_server_compare.json", tree);
    return "terminal_server_compare.json";
  }

  PassDB pass = _Passdb.getPass(pass_id);

  tree.put("passID", std::to_string(pass_id));
  tree.put("comapnyID", std::to_string(company_id));

  TimeCodeGenerator generator(pass.getprivate(), pass_id, company_id, 30);

  std::string second_src = generator.generateTimeCode();

  if (second_src == timeCode)
    tree.put("verification", "success");
  else
    tree.put("verification", "error_not_compare");

  boost::property_tree::write_json("terminal_server_compare.json", tree);
  return "terminal_server_compare.json";
}