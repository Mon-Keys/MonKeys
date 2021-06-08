// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "Client.hpp"

int main(int argc, char** argv) {
  net::io_context ioc;

  std::make_shared<ClientSession>(ioc)->run("192.168.31.234", "8080",
                                            "/timecode", 11);

  ioc.run();

  return EXIT_SUCCESS;
}
