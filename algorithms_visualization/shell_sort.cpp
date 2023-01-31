#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <iostream>

const int count = 213;
const int width = 9;

void sort(int *arr, int n) {
  for (int j = n; j < count; j++) {
    int temp = arr[j];
    int i = 0;
    for (i = j; i >= n && arr[i - n] > temp; i -= n)
      arr[i] = arr[i - n];
    arr[i] = temp;
  }
}
int main() {
  srand(time(0));
  sf::RenderWindow window(sf::VideoMode(count * width, 1080), "Shell Sort");
  window.setFramerateLimit(10);
  int arr[count];
  for (int i = 0; i < count; i++)
    arr[i] = i;
  std::random_shuffle(std::begin(arr), std::end(arr));
  sf::Color colors[count];
  for (int i = 0; i < count; i++) {
    colors[i] = sf::Color(rand() % 255, rand() % 255, rand() % 255);
  }
  bool start = false;
  int first = count / 2;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      start = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {

      start = 0;
      std::random_shuffle(std::begin(arr), std::end(arr));
      first = count / 2;
    }

    window.clear(sf::Color::Black);
    for (int i = 0; i < count; i++) {
      sf::RectangleShape rect(sf::Vector2f(width, arr[i] * 4));
      rect.setOrigin(0, rect.getSize().y);
      rect.setPosition(sf::Vector2f(i * width, window.getSize().y));
      rect.setFillColor(colors[i]);
      rect.setOutlineColor(sf::Color::Black);
      rect.setOutlineThickness(1);
      window.draw(rect);
    }

    if (start)
      if (first > 0) {
        sort(arr, first);
        first /= 3;
      }
    window.display();
  }
}
