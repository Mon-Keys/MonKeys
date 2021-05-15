set(VISION_LIB_PATH ${PROJECT_SOURCE_DIR}/visionLib)


include_directories("${VISION_LIB_PATH}/clientHandler/include/")
include_directories("${VISION_LIB_PATH}/clientHandler/include/")
include_directories("${VISION_LIB_PATH}/database/include/")
include_directories("${VISION_LIB_PATH}/httpClient/include/")
include_directories("${VISION_LIB_PATH}/httpServer/include/")
include_directories("${VISION_LIB_PATH}/logger/include/")
include_directories("${VISION_LIB_PATH}/terminalClient/include/")
include_directories("${VISION_LIB_PATH}/timecode/include/")
include_directories("${VISION_LIB_PATH}/terminalServer/include/")
include_directories("${VISION_LIB_PATH}/terminalHandler/include/")
include_directories("${VISION_LIB_PATH}/terminalHandler/include/")

find_package(Boost REQUIRED)
include_directories(${Boost_LIBRARIES})

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

file(GLOB tests "${VISION_LIB_PATH}/test/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main.cpp")

foreach(file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}Test"
            ${file}
            "${VISION_LIB_PATH}/test/main.cpp" )
    target_link_libraries("${name}Test" gtest_main visionLib gmock_main -lboost_thread -lboost_system ${PQXX_LIB} ${PQ_LIB})
    
    add_test(NAME ${name} COMMAND "${name}Test")
endforeach()



# <SOURCE_DIR>
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
# </SOURCE_DIR>