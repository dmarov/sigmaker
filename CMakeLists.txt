cmake_minimum_required(VERSION 3.18.0)
project(sigmaker VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(sqlite3 CONFIG REQUIRED)

file(GLOB modules_src
    "src/modules/*.cpp"
)

add_executable(sigmaker src/main.cpp ${modules_src})
target_link_libraries(sigmaker PRIVATE sqlite3)

install(TARGETS sigmaker DESTINATION bin)
