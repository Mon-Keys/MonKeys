#include "gtest/gtest.h"
#include "../include/httpClient.hpp"


TEST(TestHttpClient, correct_log_in) {
    HttpClient client;
    const char *url = "http://mail.ru";
    client.establishConnection(url);
    client.logIn();
    EXPECT_TRUE(client.getIsLogIn());
    client.breakConection();    
}

TEST(TestHttpClient, unauthorized_client) {
    HttpClient client;
    const char *url = "http://mail.ru";
    client.establishConnection(url);
    EXPECT_FALSE(client.getIsLogIn());
    client.breakConection();
}

TEST(TestHttpClient, correct_log_out) {
    HttpClient client;
    const char *url = "http://mail.ru";
    client.establishConnection(url);
    client.logIn();
    client.logOut();
    EXPECT_FALSE(client.getIsLogIn());
    client.breakConection();    
}

TEST(TestHttpClient, correct_registration) {
    HttpClient client;
    const char *url = "http://mail.ru";
    client.establishConnection(url);
    client.registerClient();
    EXPECT_TRUE(client.getIsLogIn());
    client.breakConection();
}

class TestGetPasses: public ::testing::Test {
 protected:
    void SetUp() {
        client.establishConnection(url);
        examplePasses = new long[4];
        examplePasses[0] = 4;
        examplePasses[1] = 6;
        examplePasses[2] = 9;
        examplePasses[3] = 14;
        client.setPasses(examplePasses);
    }
    void TearDown() {
        delete []examplePasses;
        client.breakConection();
    }
    const char *url = "http://mail.ru";
    HttpClient client;
    long *examplePasses;
};

TEST_F(TestGetPasses, correct_get_passes) {
    client.getPasses();
}


TEST(TestHttpClient, correct_connecton_establishing) {
    HttpClient client;
    const char *url = "http://mail.ru";
    client.establishConnection(url);
    EXPECT_TRUE(client.getIsConnected());
    client.breakConection();
}
