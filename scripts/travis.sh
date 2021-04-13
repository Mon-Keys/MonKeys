#!/bin/bash

cd .. 
cppcheck --enable=all --language=c++ visionLib/source/*.cpp visionLib/test/*.cpp --suppress=missingInclude --suppress=unusedFunction
cppcheck --enable=all --language=c++ terminalClient/main.cpp --suppress=missingInclude --suppress=unusedFunction
cppcheck --enable=all --language=c++ userClient/main.cpp --suppress=missingInclude --suppress=unusedFunction
cppcheck --enable=all --language=c++ terminalServer/main.cpp --suppress=missingInclude --suppress=unusedFunction
cppcheck --enable=all --language=c++ userServer/main.cpp --suppress=missingInclude --suppress=unusedFunction
cpplint --extensions=cpp visionLib/source/*.cpp visionLib/test/*.cpp 
cpplint --extensions=hpp visionLib/include/*.hpp 
cpplint --extensions=cpp terminalClient/main.cpp 
cpplint --extensions=cpp userClient/main.cpp 
cpplint --extensions=cpp terminalServer/main.cpp 
cpplint --extensions=cpp userServer/main.cpp 
rm -rf build
mkdir build && cd build
cmake .. 
make

