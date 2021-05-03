#!/bin/bash
clang-format -i -style=Google ../visionLib/include/*.hpp ../visionLib/source/*.cpp ../visionLib/test/*.cpp 
clang-format -i -style=Google ../terminalClient/main.cpp 
clang-format -i -style=Google ../userClient/main.cpp 
clang-format -i -style=Google ../terminalServer/main.cpp 
clang-format -i -style=Google ../userServer/main.cpp 