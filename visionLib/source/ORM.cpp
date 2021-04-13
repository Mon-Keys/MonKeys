// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "../include/ORM.hpp"

#include <iostream>

ORM::ClientDB ORM::getClientData(uint64_t ID) { return ClientDB(); }

ORM::CompanyDB ORM::getCompanyData(uint64_t ID) { return CompanyDB(); }

ORM::PassDB ORM::getPassData(uint64_t ID) { return PassDB(); }
