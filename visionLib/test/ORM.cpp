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

class DB : public DataBase {
  DataBase& dbC;

 public:
  explicit DB(DataBase& _dbC) : dbC(_dbC) {}
};

class MockDBC : public DataBaseConnect {
 public:
  MOCK_METHOD2(logIn, bool(std::string username, std::string password));
  MOCK_METHOD1(logOut, bool(std::string username));
};

class MockDBPassExist : public DataBase {
 public:
  MOCK_METHOD1(sqlReqForPass,
               std::vector<PassDB>(const std::string& sql_request));
};

class MockDBClientExist : public DataBase {
 public:
  MOCK_METHOD1(sqlReqForClient,
               std::vector<ClientDB>(const std::string& sql_request));
};

class MockDBCompanyExist : public DataBase {
 public:
  MOCK_METHOD1(sqlReqForCompany,
               std::vector<CompanyDB>(const std::string& sql_request));
};

class MockDBPassageExist : public DataBase {
 public:
  MOCK_METHOD1(sqlReqForPassage,
               std::vector<PassageDB>(const std::string& sql_request));
};

class MockDBInsert : public DataBase {
 public:
  MOCK_METHOD1(sql_req_for_insert, uint64_t(const std::string& sql_request));
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

TEST(DBInsertTest, InsertPassTest) {
  MockDBInsert mcdb;
  DB db(mcdb);

  PassDB pass;

  ON_CALL(mcdb, sql_req_for_insert(_)).WillByDefault(Return(1));

  uint64_t res = db.insertPass(pass);
  EXPECT_EQ(res, 1);
}

TEST(DBInsertTest, InsertClientTest) {
  MockDBInsert mcdb;
  DB db(mcdb);

  ClientDB client;

  ON_CALL(mcdb, sql_req_for_insert(_)).WillByDefault(Return(1));

  uint64_t res = db.insertClient(client);
  EXPECT_EQ(res, 1);
}

TEST(DBInsertTest, InsertCompanyTest) {
  MockDBInsert mcdb;
  DB db(mcdb);

  CompanyDB company;

  ON_CALL(mcdb, sql_req_for_insert(_)).WillByDefault(Return(1));

  uint64_t res = db.insertCompany(company);
  EXPECT_EQ(res, 1);
}

TEST(DBInsertTest, InsertPassageTest) {
  MockDBInsert mcdb;
  DB db(mcdb);

  PassageDB passage;

  ON_CALL(mcdb, sql_req_for_insert(_)).WillByDefault(Return(1));

  uint64_t res = db.insertPassage(passage);
  EXPECT_EQ(res, 1);
}

TEST(DBExistsTest, TestPassExists) {
  MockDBPassExist mcdb;
  DB db(mcdb);

  std::vector<PassDB> res;

  for (int i = 1; i < 3; i++) {
    PassDB pass;
    pass.setClientID(i);
    pass.setID(i);
    pass.setprivate(STR);
    pass.setCompanyID(i);  // NOLINT
    res.push_back(pass);
  }

  for (auto& iter : res) {
    std::cout << iter.getID() << std::endl;
    std::cout << iter.getprivate() << std::endl;
    std::cout << iter.getCompanyID() << std::endl;
    std::cout << iter.getClientID() << std::endl;
  }

  ON_CALL(mcdb, sqlReqForPass(_)).WillByDefault(Return(res));

  bool ex = db.PassExists(1);
  EXPECT_TRUE(ex);
}

TEST(DBExistsTest, TestCompanyExists) {
  MockDBCompanyExist mcdb;
  DB db(mcdb);

  std::vector<CompanyDB> res;

  for (int i = 0; i < 3; i++) {
    CompanyDB company;
    company.setID(i);
    company.setName("sdgds");
    res.push_back(company);
  }

  ON_CALL(mcdb, sqlReqForCompany(_)).WillByDefault(Return(res));

  bool ex = db.CompanyExists(1);
  EXPECT_TRUE(ex);
}

TEST(DBExistsTest, TestClientExists) {
  MockDBClientExist mcdb;
  DB db(mcdb);

  std::vector<ClientDB> res;

  for (int i = 0; i < 3; i++) {
    ClientDB client;
    client.setID(i);
    client.setLogin("login");
    client.setPassword("password");
    client.setEmail("inagdimaev@mail.ru");
    res.push_back(client);
  }

  ON_CALL(mcdb, sqlReqForClient(_)).WillByDefault(Return(res));

  bool ex = db.ClientExists(1);
  EXPECT_TRUE(ex);
}

TEST(DBExistsTest, TestPassageExists) {
  MockDBPassageExist mcdb;
  DB db(mcdb);

  std::vector<PassageDB> res;

  time_t time_now = time(NULL);

  for (int i = 0; i < 3; i++) {
    PassageDB passage;
    passage.setID(i);
    passage.setActionType(0);
    passage.setTime(time_now);
    passage.setPassID(i);
    res.push_back(passage);
  }

  ON_CALL(mcdb, sqlReqForPassage(_)).WillByDefault(Return(res));

  bool ex = db.PassageExists(1);
  EXPECT_TRUE(ex);
}
