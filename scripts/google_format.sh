#!/bin/bash

clang-format -i -style=Google ../visionLib/clientHandler/include/*.hpp
clang-format -i -style=Google ../visionLib/database/include/*.hpp
clang-format -i -style=Google ../visionLib/httpClient/include/*.hpp
clang-format -i -style=Google ../visionLib/httpServer/include/*.hpp
clang-format -i -style=Google ../visionLib/logger/include/*.hpp
clang-format -i -style=Google ../visionLib/terminalClient/include/*.hpp
clang-format -i -style=Google ../visionLib/terminalHandler/include/*.hpp
clang-format -i -style=Google ../visionLib/terminalServer/include/*.hpp
clang-format -i -style=Google ../visionLib/terminalHandler/include/*.hpp

clang-format -i -style=Google ../visionLib/test/*.cpp 
clang-format -i -style=Google ../visionLib/clientHandler/source/*.cpp
clang-format -i -style=Google ../visionLib/database/source/*.cpp
clang-format -i -style=Google ../visionLib/httpClient/source/*.cpp
clang-format -i -style=Google ../visionLib/httpServer/source/*.cpp
clang-format -i -style=Google ../visionLib/logger/source/*.cpp
clang-format -i -style=Google ../visionLib/terminalClient/source/*.cpp
clang-format -i -style=Google ../visionLib/terminalHandler/source/*.cpp
clang-format -i -style=Google ../visionLib/terminalServer/source/*.cpp
clang-format -i -style=Google ../visionLib/terminalHandler/source/*.cpp