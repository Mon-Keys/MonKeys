// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "clientHandler.hpp"
#include "database.hpp"

#define STR "lolahah"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;

TEST(ConnectTEST, TestConnect) {
  std::map<std::string, std::string> lol{{"dbname", "Monkeys"},
                                         {"host", "localhost"},
                                         {"user", "postgres"},
                                         {"password", "password"}};
  DataBase db(lol);
}

TEST(ClientExistTEST, ClientExistTrue) {
  std::map<std::string, std::string> lol{{"dbname", "Monkeys"},
                                         {"host", "localhost"},
                                         {"user", "postgres"},
                                         {"password", "password"}};
  ClientDataBase Cdb(lol);

  bool flag = Cdb.ClientExists("Ilyagu");

  EXPECT_TRUE(flag);
}

TEST(ClientExistTEST, ClientExistFalse) {
  std::map<std::string, std::string> lol{{"dbname", "Monkeys"},
                                         {"host", "localhost"},
                                         {"user", "postgres"},
                                         {"password", "password"}};
  ClientDataBase Cdb(lol);

  bool flag = Cdb.ClientExists("gsmg");

  EXPECT_FALSE(flag);
}

TEST(getClientTEST, getClientTest) {
  std::map<std::string, std::string> lol{{"dbname", "Monkeys"},
                                         {"host", "localhost"},
                                         {"user", "postgres"},
                                         {"password", "password"}};
  ClientDataBase Cdb(lol);

  ClientDB temp = Cdb.getClient("Ilyagu");

  EXPECT_EQ(temp.getID(), 4);
  bool flag = false;
  if (temp.getLogin() == "Ilyagu")
    flag = true;
  else
    flag = false;
  EXPECT_TRUE(flag);
  if (temp.getEmail() == "inagdimaev@mail.ru")
    flag = true;
  else
    flag = false;
  EXPECT_TRUE(flag);
  if (temp.getPassword() == "12345")
    flag = true;
  else
    flag = false;
  EXPECT_TRUE(flag);
}

TEST(insertClietnTEST, insertClient) {
  ClientDataBase Cdb;

  bool flag = Cdb.insertClient("Oleg", "kozinov@gmail.com", "iamretard");

  EXPECT_TRUE(flag);
}

TEST(logInTEST, logInTestCorrect) {
  clientHandler CLH;

  bool flag = CLH.logInClient("Ilyagu", "12345");

  EXPECT_TRUE(flag);
}

TEST(logInTEST, logInTestInCorrect) {
  clientHandler CLH;

  bool flag = CLH.logInClient("Ilyagu", "incorrentpassword");

  EXPECT_FALSE(flag);
}

TEST(logInTEST, logInTestNotExists) {
  clientHandler CLH;

  bool flag = CLH.logInClient("fasdf", "12345");

  EXPECT_FALSE(flag);
}

TEST(registerTEST, registerCorrect) {
  clientHandler CLH;

  bool flag = CLH.registerClient("Fedya", "ahah@mail.ru", "blacksnow2K21");

  EXPECT_TRUE(flag);
}

TEST(registerTEST, registerInCorrect) {
  clientHandler CLH;

  bool flag = CLH.registerClient("Ilyagu", "lol@mail.ru", "12345");

  EXPECT_FALSE(flag);
}

// class PDB {
//   DataBase& dbC;

//  public:
//   explicit PDB(DataBase& _dbC) : dbC(_dbC) {}

//   uint64_t testinsertPass(const PassDB& Pass) {
//     return dbC.sql_req_for_insert("fsdf");
//   }
// };

// class ClDB {
//   DataBase& dbC;

//  public:
//   explicit ClDB(DataBase& _dbC) : dbC(_dbC) {}

//   uint64_t testinsertClient(const ClientDB& Client) {
//     return dbC.sql_req_for_insert("fsdf");
//   }
// };

// class CoDB {
//   DataBase& dbC;

//  public:
//   explicit CoDB(DataBase& _dbC) : dbC(_dbC) {}

//   uint64_t testinsertCompany(const CompanyDB& Company) {
//     return dbC.sql_req_for_insert("fsdf");
//   }
// };

// class PaDB {
//   DataBase& dbC;

//  public:
//   explicit PaDB(DataBase& _dbC) : dbC(_dbC) {}

//   uint64_t testinsertPassage(const PassageDB& Passage) {
//     return dbC.sql_req_for_insert("fsdf");
//   }
// };

// class MockDBC : public DataBase {
//  public:
//   MOCK_METHOD2(logIn, bool(std::string username, std::string password));
//   MOCK_METHOD1(logOut, bool(std::string username));
// };

// class MockDBPassExist : public PassDataBase {
//  public:
//   MOCK_METHOD1(sqlReq, std::vector<PassDB>(const std::string& sql_request));
// };

// class MockDBClientExist : public ClientDataBase {
//  public:
//   MOCK_METHOD1(sqlReq, std::vector<ClientDB>(const std::string&
//   sql_request));
// };

// class MockDBCompanyExist : public CompanyDataBase {
//  public:
//   MOCK_METHOD1(sqlReq, std::vector<CompanyDB>(const std::string&
//   sql_request));
// };

// class MockDBPassageExist : public PassageDataBase {
//  public:
//   MOCK_METHOD1(sqlReq, std::vector<PassageDB>(const std::string&
//   sql_request));
// };

// class MockDBInsert : public DataBase {
//  public:
//   MOCK_METHOD1(sql_req_for_insert, uint64_t(const std::string& sql_request));
// };

// TEST(MyDBTest, LoginTest) {
//   MockDBC mcdb;
//   MyDataBase db(mcdb);

//   EXPECT_CALL(mcdb, logIn("lol", "kek"))
//       .Times(AtLeast(1))
//       .WillOnce(Return(true));

//   bool res = db.init("lol", "kek");
//   EXPECT_TRUE(res);
// }

// TEST(DBInsertTest, InsertPassTest) {
//   MockDBInsert mcdb;
//   PDB db(mcdb);

//   PassDB pass(0, "lol", 0, 0);

//   ON_CALL(mcdb, sql_req_for_insert(_)).WillByDefault(Return(1));

//   uint64_t res = db.testinsertPass(pass);
//   EXPECT_EQ(res, 1);
// }

// TEST(DBInsertTest, InsertClientTest) {
//   MockDBInsert mcdb;
//   ClDB db(mcdb);

//   ClientDB client(0, "kek", "mail", "password");

//   ON_CALL(mcdb, sql_req_for_insert(_)).WillByDefault(Return(1));

//   uint64_t res = db.testinsertClient(client);
//   EXPECT_EQ(res, 1);
// }

// TEST(DBInsertTest, InsertCompanyTest) {
//   MockDBInsert mcdb;
//   CoDB db(mcdb);

//   CompanyDB company(0, "company_name");

//   ON_CALL(mcdb, sql_req_for_insert(_)).WillByDefault(Return(1));

//   uint64_t res = db.testinsertCompany(company);
//   EXPECT_EQ(res, 1);
// }

// TEST(DBInsertTest, InsertPassageTest) {
//   MockDBInsert mcdb;
//   PaDB db(mcdb);

//   PassageDB passage(0, time(NULL), 0, 0);

//   ON_CALL(mcdb, sql_req_for_insert(_)).WillByDefault(Return(1));

//   uint64_t res = db.testinsertPassage(passage);
//   EXPECT_EQ(res, 1);
// }

// TEST(DBExistsTest, TestPassExists) {
//   MockDBPassExist mcdb;
//   PassDataBase db;

//   std::vector<PassDB> res;

//   for (int i = 1; i < 3; i++) {
//     PassDB pass(i, STR, i, i);
//     res.push_back(pass);
//   }

//   ON_CALL(mcdb, sqlReq(_)).WillByDefault(Return(res));

//   bool ex = db.PassExists(1);
//   EXPECT_TRUE(ex);
// }

// TEST(DBExistsTest, TestCompanyExists) {
//   MockDBCompanyExist mcdb;
//   CompanyDataBase db;

//   std::vector<CompanyDB> res;

//   for (int i = 0; i < 3; i++) {
//     CompanyDB company(i, STR);
//     res.push_back(company);
//   }

//   ON_CALL(mcdb, sqlReq(_)).WillByDefault(Return(res));

//   bool ex = db.CompanyExists(1);
//   EXPECT_TRUE(ex);
// }

// TEST(DBExistsTest, TestClientExists) {
//   MockDBClientExist mcdb;
//   ClientDataBase db;

//   std::vector<ClientDB> res;

//   for (int i = 0; i < 3; i++) {
//     ClientDB client(i, STR, STR, STR);
//     res.push_back(client);
//   }

//   ON_CALL(mcdb, sqlReq(_)).WillByDefault(Return(res));

//   bool ex = db.ClientExists(1);
//   EXPECT_TRUE(ex);
// }

// TEST(DBExistsTest, TestPassageExists) {
//   MockDBPassageExist mcdb;
//   PassageDataBase db;

//   std::vector<PassageDB> res;

//   time_t time_now = time(NULL);

//   for (int i = 0; i < 3; i++) {
//     PassageDB passage(i, time_now, 0, i);
//     res.push_back(passage);
//   }

//   ON_CALL(mcdb, sqlReq(_)).WillByDefault(Return(res));

//   bool ex = db.PassageExists(1);
//   EXPECT_TRUE(ex);
// }
