cmake_minimum_required(VERSION 3.21)
project(kuest)

set(CMAKE_CXX_STANDARD 23)
add_executable(kuest main.cpp)
target_link_libraries(kuest sqlite3)
configure_file(kuest.db kuest.db COPYONLY)
