project(Tetris)
set(SFMLLinkers -lsfml-graphics -lsfml-window -lsfml-system)
add_executable(sf-app main.cpp Source/Game.cpp Source/Piece.cpp Source/Stats.cpp Source/Board.cpp)
target_link_libraries(sf-app ${SFMLLinkers})
