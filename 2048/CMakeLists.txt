project(2048)
set(SFMLLinkers -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lX11)
add_executable(sf-2048 main.cpp src/Game.cpp src/Board.cpp src/Block.cpp)
target_link_libraries(sf-2048 ${SFMLLinkers})
