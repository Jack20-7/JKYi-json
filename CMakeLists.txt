cmake_minimum_required(VERSION 3.12)
project(json)

set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O1 -fPIC -ggdb -std=c++17 -Wall -Wno-deprecated -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")

set (SRC
    json/json.cc
    json/Parser.cc
    )

add_library(json SHARED ${SRC})

add_executable(test01 test/test01.cc)
target_link_libraries(test01 json)

add_executable(test_parser test/test_parser.cc)
target_link_libraries(test_parser json)

add_executable(test03 test/test03.cc)
target_link_libraries(test03 json)

add_executable(test_speed test/test_speed.cc)
target_link_libraries(test_speed json)

#将生成的目标文件放到bin目录下
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#将生成的动态库放到lib目录下
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


