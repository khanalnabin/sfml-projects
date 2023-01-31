project(sf_utilities)
set(SFMLLinkers -lsfml-graphics -lsfml-audio -lsfml-network -lsfml-window
                -lsfml-system)
add_executable(sf-utilities demo.cpp Textbox/Textbox.cpp Button/Button.cpp)
target_link_libraries(sf-utilities ${SFMLLinkers})
