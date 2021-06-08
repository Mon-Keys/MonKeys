// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "httpServer.hpp"

int main(int argc, char* argv[]) {
  const boost::asio::ip::address address =
      net::ip::make_address("192.168.31.234");
  const unsigned short port = static_cast<unsigned short>(std::atoi("8080"));
  const std::shared_ptr<std::string> doc_root =
      std::make_shared<std::string>(".");
  const int threads = 1;

  net::io_context ioc{threads};

  std::make_shared<Listener>(ioc, tcp::endpoint{address, port}, doc_root)
      ->run();

  std::vector<std::thread> v;
  v.reserve(threads - 1);
  for (auto i = threads - 1; i > 0; --i) {
    v.emplace_back([&ioc] { ioc.run(); });
  }

  ioc.run();

  return EXIT_SUCCESS;
}
