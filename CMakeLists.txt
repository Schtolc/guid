cmake_minimum_required (VERSION 3.0)

project (guid)

add_executable(guid test.cc)
target_link_libraries(guid benchmark uuid pthread)

set (CMAKE_CXX_FLAGS "-std=c++14 -Werror")
