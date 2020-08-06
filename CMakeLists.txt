cmake_minimum_required(VERSION 3.18.0)
project(FPS VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(sqlite3 CONFIG REQUIRED)
find_package(GLUT REQUIRED)

file(GLOB modules_src
    "src/modules/*.cpp"
)

add_executable(FPS src/main.cpp ${modules_src})
target_link_libraries(FPS PRIVATE sqlite3 GLUT::GLUT)

install(TARGETS FPS DESTINATION bin)
