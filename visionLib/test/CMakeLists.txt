set(VISION_LIB_PATH ${PROJECT_SOURCE_DIR}/visionLib)


include_directories("${VISION_LIB_PATH}/include")



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