// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "ORM.hpp"

#define STR "lolahah"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;

class MyDataBase {
  DataBaseConnect& dbC;

 public:
  explicit MyDataBase(DataBaseConnect& _dbC) : dbC(_dbC) {}

  int init(std::string username, std::string password) {
    if (dbC.logIn(username, password) == false) {
      std::cout << "DB_FAIL" << std::endl;
      return -1;
    } else {
      std::cout << "DB_SUCCESS" << std::endl;
      return 1;
    }
  }
};

// class DB {
//   DataBase& dbC;

//  public:
//   explicit DB(DataBase& _dbC) : dbC(_dbC) {}

//   uint64_t insertPasslol(const PassDB Pass) { return dbC.insertPass(Pass); }
//   uint64_t insertPassagelol(const PassageDB Passage) {
//     return dbC.insertPassage(Passage);
//   }
//   uint64_t insertClientlol(const ClientDB Client) {
//     return dbC.insertClient(Client);
//   }
//   uint64_t insertCompanylol(const CompanyDB Company) {
//     return dbC.insertCompany(Company);
//   }

//   // bool PassExists(const uint64_t PassID) {
//   //   std::vector<PassDB> res = dbC.sql_req("skjfh");
//   //   for (auto& iter : res) {
//   //     if (iter.getID() == PassID) {
//   //       return true;
//   //     }
//   //   }
//   //   return false;
//   // }
//   // bool ClientExists(const uint64_t ClientID) {
//   //   std::vector<ClientDB> res = dbC.sql_req("skjfh");
//   //   for (auto& iter : res) {
//   //     if (iter.getID() == ClientID) {
//   //       return true;
//   //     }
//   //   }
//   //   return false;
//   // }
//   // bool CompanyExists(const uint64_t CompanyID) {
//   //   std::vector<CompanyDB> res = dbC.sql_req("skjfh");
//   //   for (auto& iter : res) {
//   //     if (iter.getID() == CompanyID) {
//   //       return true;
//   //     }
//   //   }
//   //   return false;
//   // }
//   // bool PassageExistslol(const uint64_t PassageID) {
//   //   std::vector<PassageDB> res = dbC.sql_req("skjfh");
//   //   for (auto& iter : res) {
//   //     if (iter.getID() == PassageID) {
//   //       return true;
//   //     }
//   //   }
//   //   return false;
//   // }
// };

class MockDBC : public DataBaseConnect {
 public:
  MOCK_METHOD2(logIn, bool(std::string username, std::string password));
  MOCK_METHOD1(logOut, bool(std::string username));
};

// class MockDBPassExist : public DataBase {
//  public:
//   MOCK_METHOD1(sql_req, std::vector<PassDB>(const std::string& sql_request));
// };

// class MockDBClientExist : public DataBase {
//  public:
//   MOCK_METHOD1(sql_req, std::vector<ClientDB>(const std::string& sql_request));
// };

// class MockDBCompanyExist : public DataBase {
//  public:
//   MOCK_METHOD1(sql_req, std::vector<CompanyDB>(const std::string& sql_request));
// };

// class MockDBPassageExist : public DataBase {
//  public:
//   MOCK_METHOD1(sql_req, std::vector<PassageDB>(const std::string& sql_request));
// };

class MockDBInsert : public DataBase {
 public:
  MOCK_METHOD1 (sql_req_for_insert, uint64_t (const std::string& sql_request));
};

TEST(MyDBTest, LoginTest) {
  MockDBC mcdb;
  MyDataBase db(mcdb);

  EXPECT_CALL(mcdb, logIn("lol", "kek"))
      .Times(AtLeast(1))
      .WillOnce(Return(true));

  bool res = db.init("lol", "kek");
  EXPECT_EQ(res, 1);
}

TEST(DBTest, InsertTest) {
  MockDBInsert mcdb;
  DataBase db(mcdb);

  PassDB pass;

  ON_CALL(mcdb, sql_req_for_insert(_)).WillByDefault(Return(1));

  uint64_t res = db.insertPass(pass);
  EXPECT_EQ(res, 1);
}

// TEST(DBTest, TestPassExists) {
//   MockDBPassExist mcdb;
//   DB db(mcdb);

//   std::vector<PassDB> res;

//   for (int i = 0; i < 3; i++) {
//     PassDB pass;
//     pass.setClientID(i);
//     pass.setID(i);
//     pass.setprivate(STR);
//     pass.setCompanyID(i);
//     res.push_back(pass);
//   }

//   EXPECT_CALL(mcdb, sql_req(_)).Times((1)).WillOnce(Return(res));

//   bool ex = db.PassExists(1);
//   EXPECT_EQ(ex, true);
// }

// TEST(DBTest, TestCompanyExists) {
//   MockDBCompanyExist mcdb;
//   DB db(mcdb);

//   std::vector<CompanyDB> res;

//   for (int i = 0; i < 3; i++) {
//     CompanyDB company;
//     company.setID(i);
//     company.setName("sdgds");
//     res.push_back(company);
//   }

//   EXPECT_CALL(mcdb, sql_req(_)).Times((1)).WillOnce(Return(res));

//   bool ex = db.CompanyExists(1);
//   EXPECT_EQ(ex, true);
// }

// TEST(DBTest, TestClientExists) {
//   MockDBClientExist mcdb;
//   DB db(mcdb);

//   std::vector<ClientDB> res;

//   for (int i = 0; i < 3; i++) {
//     ClientDB client;
//     client.setID(i);
//     client.setLogin("login");
//     client.setPassword("password");
//     client.setEmail("inagdimaev@mail.ru");
//     res.push_back(client);
//   }

//   EXPECT_CALL(mcdb, sql_req(_)).Times((1)).WillOnce(Return(res));

//   bool ex = db.PassExists(1);
//   EXPECT_EQ(ex, true);
// }

// TEST(DBTest, TestPassageExists) {
//   MockDBPassExist mcdb;
//   DB db(mcdb);

//   std::vector<PassageDB> res;

//   time_t time_lol = time();

//   for (int i = 0; i < 3; i++) {
//     PassageDB passage;
//     passage.setID(i);
//     passage.setActionType(0);
//     passage.setTime(time_lol);
//     passage.setPassID(i);
//     res.push_back(passage);
//   }

//   EXPECT_CALL(mcdb, sql_req(_)).Times((1)).WillOnce(Return(res));

//   bool ex = db.PassExists(1);
//   EXPECT_EQ(ex, true);
// }
