cmake_minimum_required(VERSION 3.16.3)
project(vision)

set(Boost_USE_MULTITHREAD ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic -pedantic -fprofile-arcs -ftest-coverage -lpqxx -lpq")

find_package(Boost)
include_directories(${Boost_LIBRARIES})

# Building lib
set(VISION_LIB_PATH ${PROJECT_SOURCE_DIR}/visionLib)

file(GLOB sources "${VISION_LIB_PATH}/source/*.cpp")
file(GLOB headers "${VISION_LIB_PATH}/include/*.hpp")


add_library(visionLib SHARED ${sources} ${headers})
# Building lib

# <Test>
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
      ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(${VISION_LIB_PATH}/test)

# </Test>


### DEBUG BUILD
set(CMAKE_BUILD_TYPE DEBUG)
###


### <-->

#TerminalClient
add_executable(terminalClient ${PROJECT_SOURCE_DIR}/terminalClient/main.cpp)
target_link_libraries(terminalClient visionLib ${Boost_LIBRARIES} -lboost_thread ${PQXX_LIB} ${PQ_LIB})
target_include_directories(terminalClient PUBLIC "${VISION_LIB_PATH}/include")

#TerminalServer
add_executable(terminalServer ${PROJECT_SOURCE_DIR}/terminalServer/main.cpp)
target_link_libraries(terminalServer visionLib ${Boost_LIBRARIES} -lboost_thread ${PQXX_LIB} ${PQ_LIB})
target_include_directories(terminalServer PUBLIC "${VISION_LIB_PATH}/include")

#UserClient
add_executable(userClient ${PROJECT_SOURCE_DIR}/userClient/main.cpp)
target_link_libraries(userClient visionLib ${Boost_LIBRARIES} -lboost_thread ${PQXX_LIB} ${PQ_LIB})
target_include_directories(userClient PUBLIC "${VISION_LIB_PATH}/include")

#UserServer
add_executable(userServer ${PROJECT_SOURCE_DIR}/userServer/main.cpp)
target_link_libraries(userServer visionLib ${Boost_LIBRARIES} -lboost_thread ${PQXX_LIB} ${PQ_LIB})
target_include_directories(userServer PUBLIC "${VISION_LIB_PATH}/include")

### <-->