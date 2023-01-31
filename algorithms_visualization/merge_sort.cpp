#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

const int count = 213;
const int width = 9;

int min(int x, int y) { return (x < y) ? x : y; }
void merge(int arr[], int l, int m, int r);
void merge_sort(int arr[], int curr_size) {
  for (int left_start = 0; left_start < count - 1;
       left_start += 2 * curr_size) {
    // Find ending point of left subarray. mid+1 is starting
    // point of right
    int mid = min(left_start + curr_size - 1, count - 1);

    int right_end = min(left_start + 2 * curr_size - 1, count - 1);

    // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
    merge(arr, left_start, mid, right_end);
  }
}

void Merge() {
  srand(time(0));
  int loop = 0;
  sf::RenderWindow window(sf::VideoMode(count * width, 1080), "Selection Sort");
  window.setFramerateLimit(20);
  int arr[count];
  for (int i = 0; i < count; i++)
    arr[i] = i;
  std::random_shuffle(std::begin(arr), std::end(arr));
  sf::Color colors[count];
  for (int i = 0; i < count; i++) {
    colors[i] = sf::Color(rand() % 255, rand() % 255, rand() % 255);
  }
  bool start = false;
  int curr_size = 1;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      if (!start)
        start = 1;
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

    if (start && loop > 10) {
      loop = 0;
      if (curr_size <= count - 1) {
        merge_sort(arr, curr_size);
        curr_size *= 2;
      }
    };
    loop++;
    window.display();
  }
}

void merge(int arr[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  /* create temp arrays */
  int L[n1], R[n2];

  /* Copy data to temp arrays L[] and R[] */
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

  /* Merge the temp arrays back into arr[l..r]*/
  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  /* Copy the remaining elements of L[], if there are any */
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  /* Copy the remaining elements of R[], if there are any */
  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}
