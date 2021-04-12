//
// Created by Monkeys on 11.04.2021.
//

#ifndef MONKEYS_WEBAPPLICATIONCLIENT_HPP
#define MONKEYS_WEBAPPLICATIONCLIENT_HPP

#include <string>

class WebApplicationClient {
 public:
   virtual void logIn();
   virtual void logOut();
   virtual void registerClient();
   virtual void requestPasses();
   virtual std::string getTempPass(const long passID);

   virtual void establishConnection(const char *url);
   virtual void breakConection();
};

#endif // MONKEYS_WEBAPPLICATIONCLIENT_HPP
