cmake_minimum_required(VERSION 3.19)
project(SFML)
set(CMAKE_CXX_STANDARD 14)
set(SFMLLinkers -lsfml-graphics -lsfml-window -lsfml-system)
add_executable(sf-SFML bubble_sort.cpp)
target_link_libraries(sf-SFML ${SFMLLinkers})
 
