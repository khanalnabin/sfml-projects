#include "../include/Block.h"
#include <iostream>
Block::Block(int block_size, sf::Vector2f index, int value)
    : m_block_size(block_size), m_index(index), m_value(value),
      m_position(
          sf::Vector2f(m_index.y * m_block_size, m_index.x * m_block_size)) {
  font.loadFromFile("assets/fonts/ubuntu.ttf");

  m_block.setSize(sf::Vector2f(m_block_size, m_block_size));
  m_block.setPosition(m_position);
  m_block.setFillColor(colors[static_cast<int>(std::log2(m_value + 1))]);
  m_block.setOutlineThickness(5);
  m_block.setOutlineColor(sf::Color::Transparent);

  m_text.setFont(font);
  m_text.setString(std::to_string(m_value));
  m_text.setCharacterSize(50);
  m_text.setFillColor(sf::Color::Black);
  m_text.setOrigin(m_text.getLocalBounds().width / 2.0f,
                   m_text.getLocalBounds().height / 2.0f);
  m_text.setPosition(sf::Vector2f(m_block.getPosition().x + block_size / 2.0f,
                                  m_block.getPosition().y + block_size / 2.0f -
                                      m_text.getCharacterSize() / 3.0f));
}

void Block::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_block, states);
  target.draw(m_text, states);
}

sf::Color Block::colors[12] = {
    {249, 244, 244}, {240, 228, 228}, {231, 211, 211}, {254, 156, 143},
    {254, 178, 168}, {254, 200, 193}, {250, 217, 193}, {249, 202, 167},
    {250, 240, 230}, {255, 245, 238}, {250, 235, 215}, {253, 244, 152}};
