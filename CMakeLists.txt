cmake_minimum_required(VERSION 3.21)
project(kuest)

set(CMAKE_CXX_STANDARD 23)
add_executable(kuest main.cpp Player.cpp Player.h Narrative.cpp Narrative.h Option.cpp Option.h Skills.h Story.cpp Story.h)
target_link_libraries(kuest sqlite3)
configure_file(kuest.db kuest.db COPYONLY)
