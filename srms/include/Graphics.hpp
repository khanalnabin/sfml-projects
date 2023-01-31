#pragma once
#include "Button.hpp"
#include "Students.hpp"
#include "Textbox.hpp"
#include <cstring>

extern const int width;
extern const int height;

class Graphics : public sf::Drawable, sf::Transformable {
private:
    virtual void
    draw(sf::RenderTarget &target,
         sf::RenderStates = sf::RenderStates::Default) const override;
    std::vector<Button*> buttons;
    Students students;
    std::string fontname;
    std::vector<Student> student_vector;
    void drawText(sf::RenderTarget& target, sf::RenderStates states) const;
    void addStudent();
    void deleteStudent();
    void modifyData();
    void showMarks();
    void editMarks();

public:
    Graphics();
    ~Graphics();
    void update();
    void processEvents(sf::Event &event);
    void processRealEvents(sf::RenderWindow &window);
    bool temp_window;
};
