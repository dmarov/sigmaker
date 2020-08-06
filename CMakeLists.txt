cmake_minimum_required(VERSION 3.18.0)
project(sigmaker VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB modules_src
    "src/modules/*.cpp"
)

add_executable(sigmaker src/main.cpp ${modules_src})

set_property(TARGET sigmaker PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

find_package(yaml-cpp CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

target_link_libraries(sigmaker PRIVATE yaml-cpp)
target_link_libraries(sigmaker PRIVATE unofficial::sqlite3::sqlite3)

install(TARGETS sigmaker DESTINATION bin)
