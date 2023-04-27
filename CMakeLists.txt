cmake_minimum_required(VERSION 3.10)
project(raycaster)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES raycaster/main.cpp raycaster/eventhandler.cpp raycaster/vector.cpp raycaster/camera.cpp)

add_executable(raycaster.out ${SOURCES})
target_link_libraries(raycaster.out -lsfml-graphics -lsfml-window -lsfml-system)
