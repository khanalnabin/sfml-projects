#include "Graphics.hpp"

Graphics::Graphics() : students(2, 'a'), fontname("assets/ubuntu.ttf") {
    for (int i = 0; i < 5; i++) {
        buttons.push_back(new Button(sf::Vector2f(250, 60),
                                     sf::Vector2f(50, i * 100 + 100),
                                     std::to_string(i + 1), fontname));
    }
    buttons[0]->setString("Add Student");
    buttons[1]->setString("Delete Student");
    buttons[2]->setString("Modify Student");
    buttons[3]->setString("ShowMarks");
    buttons[4]->setString("Edit Marks");
    students.returnRecord(student_vector);
}

void Graphics::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    std::string s = "STUDENT RECORD MANAGEMENT SYSTEM";
    sf::Text text;
    sf::Font font;
    font.loadFromFile(fontname);
    text.setFont(font);
    text.setString(s);
    text.setCharacterSize(40);
    text.setLetterSpacing(2);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Magenta);
    sf::FloatRect fr = text.getGlobalBounds();
    text.setPosition(width / 2.0f - fr.width / 2.0f, 0);
    target.draw(text, states);
    for (auto i : buttons)
        target.draw(*i, states);
    drawText(target, states);
}
void Graphics::update() {
    for (auto i : buttons) {
        if (i->hovered)
            i->setTextColor(sf::Color::Red);
        else
            i->setTextColor(sf::Color::Black);
    }

    if (buttons[0]->clicked)
        addStudent();
    else if (buttons[1]->clicked)
        deleteStudent();
    else if (buttons[2]->clicked)
        modifyData();
    else if (buttons[3]->clicked)
        showMarks();
    else if (buttons[4]->clicked)
        editMarks();
}

void Graphics::processEvents(sf::Event &event) {}

void Graphics::processRealEvents(sf::RenderWindow &window) {
    for (auto i : buttons)
        i->listen(window);
}

void Graphics::drawText(sf::RenderTarget &target,
                        sf::RenderStates states) const {
    sf::Text text;
    sf::Font font;
    font.loadFromFile(fontname);
    text.setFont(font);
    text.setPosition(600, 100);
    std::string s = "";
    s += " Roll no \t";
    s += "Name\t\t\t\t";
    s += "Marks Entered\n";

    for (auto i : student_vector) {
        s += " " + std::to_string(i.roll_no);
        s += "\t\t\t\t" + static_cast<std::string>(i.name);
        s += i.marksheet.filled ? "\t\t\t\tYes\n" : "\t\t\t\t\tNo\n";
    }
    text.setLineSpacing(2);
    text.setString(s);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    target.draw(text, states);
}

void Graphics::addStudent() {
    sf::RenderWindow m_window(sf::VideoMode(900, 600), "opengl-Add Student");
    Textbox name_tb({300, 60}, {200, 50}, fontname);
    Textbox roll_tb({200, 60}, {200, 150}, fontname, Type::Number);
    Button submit({120, 60}, {200, 250}, "add", fontname);
    submit.clicked = false;
    std::string error_string = "";
    sf::Text error_text;
    error_text.setString(error_string);
    sf::Font font;
    font.loadFromFile(fontname);
    error_text.setFont(font);
    error_text.setPosition(50, 350);
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            name_tb.listenForText(event);
            roll_tb.listenForText(event);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            m_window.close();
        }
        name_tb.listenForClick(m_window);
        roll_tb.listenForClick(m_window);
        submit.listen(m_window);
        if (submit.clicked) {
            error_string = "";
            Student s;
            if (name_tb.getString() != "" && roll_tb.getString() != "") {
                try {
                    std::strcpy(s.name, name_tb.getString().c_str());
                    s.roll_no = std::stoi(roll_tb.getString());
                } catch (const std::invalid_argument &e) {
                    error_string = "Invalid input";
                } catch (const std::out_of_range &e) {
                    error_string = "Invalid input";
                }
                if (error_string == "") {
                    Errors error = students.addStudent(s);
                    if (error == Errors::NO_ERROR) {
                        students.returnRecord(student_vector);
                        m_window.close();
                    } else {
                        error_string = "The student with the provided roll no "
                                       "exists.\nPlease "
                                       "delete it or enter another roll.";
                    }
                }
            }
        }
        error_text.setString(error_string);
        m_window.clear(sf::Color::Black);
        m_window.draw(name_tb);
        m_window.draw(roll_tb);
        m_window.draw(submit);
        m_window.draw(error_text);
        m_window.display();
    }
}

void Graphics::deleteStudent() {
    sf::RenderWindow m_window(sf::VideoMode(900, 600), "Delete Student");
    Textbox roll_tb({200, 60}, {200, 150}, fontname, Type::Number);
    Button remove({120, 60}, {200, 250}, "delete", fontname);
    std::string error_string = "";
    sf::Text error_text;
    error_text.setString(error_string);
    sf::Font font;
    font.loadFromFile(fontname);
    error_text.setFont(font);
    error_text.setPosition(50, 350);

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            roll_tb.listenForText(event);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            m_window.close();
        }
        roll_tb.listenForClick(m_window);
        remove.listen(m_window);
        if (remove.clicked) {
            error_string = "";
            int roll_no;
            if ("" && roll_tb.getString() != "") {
                try {
                    roll_no = std::stoi(roll_tb.getString());
                } catch (const std::invalid_argument &e) {
                    error_string = "Invalid input";
                } catch (const std::out_of_range &e) {
                    error_string = "Invalid input";
                }
                if (error_string == "") {
                    Errors error = students.deleteStudent(roll_no);
                    if (error == Errors::NO_ERROR) {
                        students.returnRecord(student_vector);
                        m_window.close();
                    } else {
                        error_string =
                            "The student with the provided roll no does not "
                            "exist.\nPlease "
                            "enter another roll.";
                    }
                }
            }
        }
        error_text.setString(error_string);
        m_window.clear(sf::Color::Black);
        m_window.draw(roll_tb);
        m_window.draw(remove);
        m_window.draw(error_text);
        m_window.display();
    }
}

void Graphics::modifyData() {
    sf::RenderWindow m_window(sf::VideoMode(900, 600), "Add Student");
    Textbox name_tb({300, 60}, {200, 50}, fontname);
    Textbox roll_tb({200, 60}, {200, 150}, fontname, Type::Number);
    Button submit({120, 60}, {200, 250}, "modify", fontname);
    submit.clicked = false;
    std::string error_string = "";
    sf::Text error_text;
    error_text.setString(error_string);
    sf::Font font;
    font.loadFromFile(fontname);
    error_text.setFont(font);
    error_text.setPosition(50, 350);
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            name_tb.listenForText(event);
            roll_tb.listenForText(event);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            m_window.close();
        }
        name_tb.listenForClick(m_window);
        roll_tb.listenForClick(m_window);
        submit.listen(m_window);
        if (submit.clicked) {
            error_string = "";
            Student s;
            if (name_tb.getString() != "" && roll_tb.getString() != "") {
                try {
                    std::strcpy(s.name, name_tb.getString().c_str());
                    s.roll_no = std::stoi(roll_tb.getString());
                } catch (const std::invalid_argument &e) {
                    error_string = "Invalid input";
                } catch (const std::out_of_range &e) {
                    error_string = "Invalid input";
                }
                if (error_string == "") {
                    Errors error = students.modifyData(s);
                    if (error == Errors::NO_ERROR) {
                        students.returnRecord(student_vector);
                        m_window.close();
                    } else {
                        error_string = "The student with the provided roll no "
                                       "exists.\nPlease "
                                       "delete it or enter another roll.";
                    }
                }
            }
        }
        error_text.setString(error_string);
        m_window.clear(sf::Color::Black);
        m_window.draw(name_tb);
        m_window.draw(roll_tb);
        m_window.draw(submit);
        m_window.draw(error_text);
        m_window.display();
    }
}

void Graphics::showMarks() {
    sf::RenderWindow m_window(sf::VideoMode(900, 600), "Show Marks");
    Textbox roll_tb({200, 60}, {200, 150}, fontname, Type::Number);
    Button submit({120, 60}, {200, 250}, "View", fontname);
    submit.clicked = false;
    std::string error_string = "";
    sf::Text error_text;
    error_text.setString(error_string);
    sf::Font font;
    font.loadFromFile(fontname);
    error_text.setFont(font);
    error_text.setPosition(50, 350);
    std::string data_string;
    sf::Text data_text;
    data_text.setFont(font);
    bool submit_clicked = false;
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            roll_tb.listenForText(event);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            m_window.close();
        }
        roll_tb.listenForClick(m_window);
        submit.listen(m_window);
        if (submit.clicked) {
            error_string = "";
            Student s;
            if (roll_tb.getString() != "") {
                try {
                    s.roll_no = std::stoi(roll_tb.getString());
                } catch (const std::invalid_argument &e) {
                    error_string = "Invalid input";
                } catch (const std::out_of_range &e) {
                    error_string = "Invalid input";
                }
                if (error_string == "") {
                    Errors error = students.showMarks(s);

                    if (error == Errors::NO_ERROR) {
                        // students.returnSingleRecord();
                        data_string +=
                            "Name: " + std::string(s.name) +
                            "\tRoll no: " + std::to_string(s.roll_no) + "\n\n";
                        data_string += "Subjects\t\t\t\t\t\t\t\t\tMarks\n\n";
                        for (int i = 0; i < 8; i++) {
                            data_string +=
                                std::string(subjects[i]) +
                                "\t\t\t\t\t\t\t\t\t" +
                                std::to_string(s.marksheet.marks[i]) + "\n";
                        }

                        students.returnRecord(student_vector);
                    } else {
                        if (error == Errors::ROLL_ABSENT) {
                            error_string =
                                "The student with the provided roll no "
                                "exists.\nPlease "
                                "delete it or enter another roll.";
                        } else {
                            error_string =
                                "The marksheet of the student is not filled";
                        }
                    }
                }
            }
            submit_clicked = true;
        }
        m_window.clear(sf::Color::Black);
        if (!submit_clicked) {
            error_text.setString(error_string);
            m_window.draw(roll_tb);
            m_window.draw(submit);
            m_window.draw(error_text);
        } else {
            data_text.setString(data_string);
            m_window.draw(data_text);
        }
        m_window.display();
    }
}

void Graphics::editMarks() {
    sf::RenderWindow m_window(sf::VideoMode(900, 600), "Edit Marks");
    Textbox roll_tb({200, 60}, {200, 150}, fontname, Type::Number);
    Button submit({120, 60}, {200, 250}, "View", fontname);
    Button edit({120, 60}, {300, 500}, "Edit", fontname);
    // submit.clicked = false;
    // edit.clicked = false;
    bool submit_clicked = false;
    std::vector<Textbox *> marks_box;
    for (int i = 0; i < 8; i++) {
        marks_box.push_back(new Textbox({100, 60}, sf::Vector2f(200, i * 70),
                                        fontname, Type::Number));
    }
    std::string error_string = "";
    sf::Text error_text;
    error_text.setString(error_string);
    sf::Font font;
    font.loadFromFile(fontname);
    error_text.setFont(font);
    error_text.setPosition(50, 350);
    std::string data_string;
    sf::Text data_text;
    data_text.setFont(font);
    std::string last_error_string = "";
    sf::Text last_error_text;
    last_error_text.setFont(font);

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (!submit_clicked) {
                roll_tb.listenForText(event);
            } else {
                for (auto &i : marks_box) {
                    i->listenForText(event);
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            m_window.close();
        }
        if (!submit_clicked) {
            roll_tb.listenForClick(m_window);
            submit.listen(m_window);
        } else {
            for (auto &i : marks_box) {
                i->listenForClick(m_window);
            }
            edit.listen(m_window);
        }
        Student s;
        if (submit.clicked && !submit_clicked) {
            error_string = "";
            if (roll_tb.getString() != "") {
                try {
                    s.roll_no = std::stoi(roll_tb.getString());
                } catch (const std::invalid_argument &e) {
                    error_string = "Invalid input";
                } catch (const std::out_of_range &e) {
                    error_string = "Invalid input";
                }
                if (error_string == "") {
                    Errors error = students.showMarks(s);
                    data_string += "Name: " + std::string(s.name) +
                                   "\tRoll no: " + std::to_string(s.roll_no) +
                                   "\n";
                    for (int i = 0; i < 8; i++) {
                        marks_box[i]->setString(
                            std::to_string(s.marksheet.marks[i]));
                    }
                    submit_clicked = true;
                }
            }
        }

        if (edit.clicked) {
            error_string = "";
            if (roll_tb.getString() != "") {
                try {
                    for (int i = 0; i < 8; i++) {
                        s.marksheet.marks[i] =
                            std::stoi(marks_box[i]->getString());
                        s.marksheet.filled = true;
                    }
                } catch (const std::invalid_argument &e) {
                    error_string = "Invalid input";
                } catch (const std::out_of_range &e) {
                    error_string = "Invalid input";
                }
                if (error_string == "") {
                    students.editMarks(s);
                    students.returnRecord(student_vector);
                    m_window.close();
                }
            }
        }

        error_text.setString(error_string);
        m_window.clear(sf::Color::Black);

        if (!submit_clicked) {
            m_window.draw(roll_tb);
            m_window.draw(submit);
        } else {
            for (int i = 0; i < 8; i++) {
                m_window.draw(*marks_box[i]);
            }
            m_window.draw(edit);
        }
        m_window.draw(data_text);
        m_window.draw(error_text);
        m_window.display();
    }
}
Graphics::~Graphics() {
    for (auto i : buttons)
        delete i;
    buttons.clear();
}
