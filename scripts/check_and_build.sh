#!/bin/bash
cd .. 

cppcheck --enable=all --language=c++ visionLib/clientHandler/source/*.cpp --suppress=missingInclude --suppress=unusedFunction
cppcheck --enable=all --language=c++ visionLib/database/source/*.cpp --suppress=missingInclude --suppress=unusedFunction
cppcheck --enable=all --language=c++ visionLib/httpClient/source/*.cpp --suppress=missingInclude --suppress=unusedFunction
cppcheck --enable=all --language=c++ visionLib/httpServer/source/*.cpp --suppress=missingInclude --suppress=unusedFunction --suppress=useStlAlgorithm
cppcheck --enable=all --language=c++ visionLib/terminalClient/source/*.cpp --suppress=missingInclude --suppress=unusedFunction
cppcheck --enable=all --language=c++ visionLib/terminalHandler/source/*.cpp --suppress=missingInclude --suppress=unusedFunction
cppcheck --enable=all --language=c++ visionLib/terminalServer/source/*.cpp --suppress=missingInclude --suppress=unusedFunction
cppcheck --enable=all --language=c++ visionLib/terminalHandler/source/*.cpp --suppress=missingInclude --suppress=unusedFunction

cpplint --extensions=cpp visionLib/test/*.cpp 
cpplint --extensions=cpp visionLib/clientHandler/source/*.cpp
cpplint --extensions=cpp visionLib/database/source/*.cpp
cpplint --extensions=cpp visionLib/httpClient/source/*.cpp
cpplint --extensions=cpp visionLib/httpServer/source/*.cpp
cpplint --extensions=cpp visionLib/terminalClient/source/*.cpp
cpplint --extensions=cpp visionLib/terminalHandler/source/*.cpp
cpplint --extensions=cpp visionLib/terminalServer/source/*.cpp
cpplint --extensions=cpp visionLib/terminalHandler/source/*.cpp


rm -rf build
mkdir build && cd build
cmake .. 
make

