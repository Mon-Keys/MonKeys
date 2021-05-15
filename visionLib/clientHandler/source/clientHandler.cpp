// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//

#include "clientHandler.hpp"
#include "database.hpp"

bool clientHandler::logInClient(const std::string& Login, const std::string& Password) {
    if (_Cldb.ClientExists(Login) == false) return false;

    ClientDB client = _Cldb.getClient(Login);

    if (client.getPassword() == Password)
        return true;
    else 
        return false;
}

bool clientHandler::logOutClient(uint64_t ClientID) { return true;}

bool clientHandler::registerClient(const std::string& Login, const std::string& Email, const std::string& Password) {
    if (_Cldb.ClientExists(Login) == true) return false;

    return _Cldb.insertClient(Login, Email, Password);
}

std::string clientHandler::getTimeCode(const std::string& Login) {return "";}
