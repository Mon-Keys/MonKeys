#!/bin/bash

sudo apt-get update
sudo apt-get install libc6-dbg
sudo apt-get install valgrind
sudo apt-get install cppcheck
sudo pip install cpplint
sudo apt-get install -f libboost-all-dev
sudo apt-get install -y libpqxx-dev
cd .. 
cppcheck --enable=all --language=c++ visionLib/source/*.cpp visionLib/test/*.cpp --suppress=missingInclude --suppress=unusedFunction
cppcheck --enable=all --language=c++ terminalClient/main.cpp --suppress=missingInclude --suppress=unusedFunction
cppcheck --enable=all --language=c++ userClient/main.cpp --suppress=missingInclude --suppress=unusedFunction
cppcheck --enable=all --language=c++ terminalServer/main.cpp --suppress=missingInclude --suppress=unusedFunction
cppcheck --enable=all --language=c++ userServer/main.cpp --suppress=missingInclude --suppress=unusedFunction
cpplint --extensions=cpp visionLib/test/*.cpp 
cpplint --extensions=cpp visionLib/clientHandler/source/*.cpp
cpplint --extensions=cpp visionLib/database/source/*.cpp
cpplint --extensions=cpp visionLib/httpClient/source/*.cpp
cpplint --extensions=cpp visionLib/httpServer/source/*.cpp
cpplint --extensions=cpp visionLib/logger/source/*.cpp
cpplint --extensions=cpp visionLib/terminalClient/source/*.cpp
cpplint --extensions=cpp visionLib/terminalHandler/source/*.cpp
cpplint --extensions=cpp visionLib/terminalServer/source/*.cpp
cpplint --extensions=cpp visionLib/terminalHandler/source/*.cpp
# cpplint --extensions=cpp terminalClient/main.cpp 
# cpplint --extensions=cpp userClient/main.cpp 
# cpplint --extensions=cpp terminalServer/main.cpp 
# cpplint --extensions=cpp userServer/main.cpp 
rm -rf build
mkdir build && cd build
cmake .. 
make

