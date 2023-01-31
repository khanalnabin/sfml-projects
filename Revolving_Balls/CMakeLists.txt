cmake_minimum_required(VERSION 3.19)
project(Revolving_Balls)

set(CMAKE_CXX_STANDARD 14)

add_executable(sf-Revolving_Balls main.cpp)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(sf-Revolving_Balls ${SFML_LIBRARIES})
endif ()
