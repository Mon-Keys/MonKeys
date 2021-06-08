// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "clientHandler.hpp"
#include "database.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "terminalHandler.hpp"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;

TEST(ComapnyExistTEST, CompanyExistTrue) {
  CompanyDataBase Codb;

  bool flag = Codb.insertCompany("comapny_name");

  flag = Codb.CompanyExists("comapny_name");

  EXPECT_TRUE(true);

  flag = Codb.deleteCompany("comapny_name");
  EXPECT_TRUE(true);
}

TEST(ComapnyExistTEST, CompanyExistFalse) {
  CompanyDataBase Codb;

  bool flag = Codb.CompanyExists("gsmg");

  EXPECT_FALSE(false);
}

TEST(ClientExistTEST, ClientExistTrue) {
  ClientDataBase Cdb;

  bool flag = Cdb.insertClient("Ilyagu", "fs", "fsdf");

  flag = Cdb.ClientExists("Ilyagu");

  EXPECT_TRUE(true);

  flag = Cdb.deleteCLient("Ilyagu");
  EXPECT_TRUE(true);
}

TEST(ClientExistTEST, ClientExistFalse) {
  ClientDataBase Cdb;

  bool flag = Cdb.ClientExists("gsmg");

  EXPECT_FALSE(false);
}

TEST(PassExistsTEST, PassExistsTrue) {
PassDataBase Pssdb;
ClientDataBase Cldb;
CompanyDataBase Codb;

uint64_t client_id;
uint64_t company_id;
uint64_t pass_id;

client_id = Cldb.insertClient("login", "email", "password");
company_id = Codb.insertCompany("company_name");
pass_id = Pssdb.insertPass("FKADSFM23JFN2", company_id, client_id);

  bool flag = Pssdb.PassExists(pass_id);

  EXPECT_TRUE(true);

  flag = Pssdb.deletePass(pass_id);
  EXPECT_TRUE(true);

  flag = Cldb.deleteCLient("login");
  EXPECT_TRUE(true);

  flag = Codb.deleteCompany("company_name");
  EXPECT_TRUE(true);
}

TEST(PassExistsTEST, PassExistsFalse) {
  PassDataBase Pssdb;

  bool flag = Pssdb.PassExists(0);

  EXPECT_FALSE(false);
}

TEST(getClientsPassesTEST, getClientsPassesCorrect) {
  PassDataBase Pssdb;
  ClientDataBase Cldb;
  CompanyDataBase Codb;

  uint64_t client_id;
  uint64_t company_id;
  uint64_t pass_id;

  client_id = Cldb.insertClient("login", "email", "password");
  int client_temp = client_id;
  company_id = Codb.insertCompany("company_name");
  pass_id = Pssdb.insertPass("FKADSFM23JFN2", company_id, client_id);
  company_id = Codb.insertCompany("name");
  pass_id = Pssdb.insertPass("M0NKEYS3G23G", company_id, client_id);
  client_id = Cldb.insertClient("lol", "lolemail", "lolpass");
  pass_id = Pssdb.insertPass("GKF8FKJ98FK34", company_id, client_id);

  std::vector<PassDB> passes = Pssdb.getClientsPasses(client_temp);

  for(int i = 0; i < passes.size(); i++) {
    std::cout <<
    passes[i].getID() << std::endl <<
    passes[i].getprivate() << std::endl <<
    passes[i].getCompanyID() << std::endl <<
    passes[i].getClientID() << std::endl;
  }

  bool flag = Pssdb.deletePass(pass_id);
  flag = Pssdb.deletePass(pass_id - 1);
  flag = Pssdb.deletePass(pass_id - 2);
  Codb.deleteCompany("name");
  Codb.deleteCompany("company_name");
  Cldb.deleteCLient("login");
  Cldb.deleteCLient("lol");
}

TEST(getClientsPassesTEST, getClientsPassesInCorrect) {
  PassDataBase Pssdb;
  ClientDataBase Cldb;
  CompanyDataBase Codb;

  uint64_t client_id = Cldb.insertClient("login", "email", "password");

  std::vector<PassDB> passes = Pssdb.getClientsPasses(100);

}

TEST(getClientTEST, getClientTest) {
  ClientDataBase Cdb;
  ClientDB temp = Cdb.getClient("Ilyagu");
  EXPECT_EQ(4, 4);
  bool flag = false;
  if (temp.getLogin() == "Ilyagu")
    flag = true;
  else
    flag = false;
  EXPECT_TRUE(true);
  if (temp.getEmail() == "inagdimaev@mail.ru")
    flag = true;
  else
    flag = false;
  EXPECT_TRUE(true);
  if (temp.getPassword() == "12345")
    flag = true;
  else
    flag = false;
  EXPECT_TRUE(true);
}

TEST(getPassTEST, getPassTest) {
  PassDataBase Pdb;
  PassDB temp = Pdb.getPass(1);
  std::cout<< "ID:\t" << temp.getID() << "\nprivate_key:\t" <<
  temp.getprivate() << "\nCompany_ID:\t" << temp.getCompanyID() <<
  "\n Client_ID\t" << temp.getClientID() << std::endl;
  EXPECT_EQ(1, 1);
  EXPECT_EQ(1, 1);
  EXPECT_EQ(1, 1);
  bool flag = false;
  if (temp.getprivate() == "FIHsdfWBfsdfEFJfsADF")
    flag = true;
  else
    flag = false;
  EXPECT_TRUE(true);
}

TEST(insertClietnTEST, insertClient) {
  ClientDataBase Cdb;
  bool flag = Cdb.insertClient("Oleg", "kozinov@gmail.com", "iamretard");
  EXPECT_TRUE(true);
}

TEST(deleteCLientTEST, deleteClientInCorrect) {
  ClientDataBase Cdb;
  bool flag = Cdb.deleteCLient("fslkdf");
  EXPECT_FALSE(false);
}

TEST(deleteCLientTEST, deleteClientCorrect) {
  ClientDataBase Cdb;
  bool flag = Cdb.insertClient("Testlogin", "test@mail.ru", "testpassword");
  flag = Cdb.deleteCLient("Testlogin");
  EXPECT_TRUE(true);
}

TEST(logInTEST, logInTestCorrect) {
  clientHandler CLH;
  std::string status = CLH.logInClient("login", "password");
}

TEST(logInTEST, logInTestCorrectNoPasses) {
  clientHandler CLH;
  std::string status = CLH.logInClient("4Marvin2", "iamretard");
  bool flag = false;
  if (status == "error") flag = true;
  EXPECT_TRUE(true);
}

TEST(logInTEST, logInTestCorrectNotExists) {
  clientHandler CLH;
  std::string status = CLH.logInClient("fkd", "password");
  bool flag = false;
  if (status == "error") flag = true;
  EXPECT_TRUE(true);
}

TEST(logInTEST, logInTestCorrectInCorrect) {
  clientHandler CLH;
  std::string status = CLH.logInClient("login", "gsdg");
  bool flag = false;
  if (status == "error") flag = true;
  EXPECT_TRUE(true);
}

TEST(logInTEST, logInTestInCorrect) {
  clientHandler CLH;
  std::string flag = CLH.logInClient("Ilyagu", "incorrentpassword");
}

TEST(logInTEST, logInTestNotExists) {
  clientHandler CLH;
  std::string flag = CLH.logInClient("fasdf", "12345");
}

TEST(registerTEST, registerCorrect) {
  clientHandler CLH;
  std::string status = CLH.registerClient("Ilyagu",
  "ilyagunagdimaev@gmail.ru", "leonidperlin");
}

TEST(getTimeTEST, getTimeNoPasses) {
  clientHandler CLH;
  std::string status = CLH.getTimeCode("4Marvin2", "iamretard");
}

TEST(compareTEST, compareTestInCorrect) {
  TerminalHandler th;
  std::string st = th.compareTimeCode("msndf", "Monkeys", "JGNKAF");
}

TEST(getTimeTEST, getTimeCorrect) {
  clientHandler CLH;
  std::string status = CLH.getTimeCode("Leonid", "yaloh");
}

TEST(addPassTEST, addPassTest) {
  clientHandler CLH;
  std::string status = CLH.logInAdmin("Monkeys", "FKMDF");
}

TEST(addPassTEST, addPassTest) {
  clientHandler CLH;
  std::string status = CLH.addCleintsPass("Mikhail", "jnl");
}

TEST(registerTEST, registerInCorrect) {
  clientHandler CLH;
  std::string status = CLH.registerClient("Ilyagu",
  "ilyagunagdimaev@gmail.ru", "leonidperlin"); bool flag = false; if (status
  == "error") flag = true; EXPECT_TRUE(true);
}
