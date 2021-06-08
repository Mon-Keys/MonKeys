// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "Client.hpp"

int main(int argc, char** argv) {
  
  // The io_context is required for all I/O
  net::io_context ioc;

  // Launch the asynchronous operation
  // std::make_shared<ClientSession>(ioc)->run(host, port, target, version);
  std::make_shared<ClientSession>(ioc)->run("192.168.31.234", "8080", "/timecode", 11);

  // Run the I/O service. The call will return when
  // the get operation is complete.
  ioc.run();

  return EXIT_SUCCESS;
}
