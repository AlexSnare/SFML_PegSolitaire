#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace sf;

int
main(int argc, char* argv[])
{

  // Объект, который, собственно, является главным окном приложения
  RenderWindow window(
    VideoMode(1920, 1080), "SFML Works!", sf::Style::Fullscreen);

  sf::VertexArray lines(sf::LinesStrip);

  float CELL_SIZE = 50.0f;

  lines.append(sf::Vertex(sf::Vector2f(0.0f, CELL_SIZE - 1), Color::White));
  lines.append(
    sf::Vertex(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1), Color::White));
  lines.append(sf::Vertex(sf::Vector2f(CELL_SIZE - 1, 0.0f), Color::White));

  float offset_h = ((ceil(1920 / CELL_SIZE) * CELL_SIZE) / 2 - 1920 / 2);
  float offset_w = ((ceil(1080 / CELL_SIZE) * CELL_SIZE) / 2 - 1080 / 2);

  std::cout << "offset_h = " << (int)offset_h << std::endl;
  std::cout << "offset_w = " << (int)offset_w << std::endl;

  sf::RenderTexture texture;
  if (!texture.create((int)CELL_SIZE, (int)CELL_SIZE))
    return -1;

  texture.clear(Color::Blue);
  texture.draw(lines);
  texture.setRepeated(true);
  texture.display();

  sf::Sprite sprite(texture.getTexture(), IntRect(0, 0, 1920, 1080));

  // sprite.setPosition(15.f, 10.f);
  sprite.move(-offset_h, -offset_w);

  // Главный цикл приложения. Выполняется, пока открыто окно
  while (window.isOpen()) {
    // Обрабатываем очередь событий в цикле
    Event event;
    while (window.pollEvent(event)) {
      // Пользователь нажал на «крестик» и хочет закрыть окно?
      if (event.type == Event::Closed)
        // тогда закрываем его
        window.close();
    }
    // Зададим фон
    window.clear(Color::Blue);

    Vertex line_horizontal[] = { // Координата первой вершины
                                 Vertex(Vector2f(0.0f, 540.0f)),
                                 // Координата второй вершины
                                 Vertex(Vector2f(1920.0f, 540.f))
    };
    Vertex line_vertical[] = { // Координата первой вершины
                               Vertex(Vector2f(960.0f, 0.0f)),
                               // Координата второй вершины
                               Vertex(Vector2f(960.0f, 1080.f))
    };

    // Устанавливаем цвет линии - красный
    line_horizontal->color = Color::Red;
    line_vertical->color = Color::Red;

    window.draw(sprite);
    // Отрисовка линии
    window.draw(line_horizontal, 2, Lines);
    window.draw(line_vertical, 2, Lines);
    // Отрисовка окна
    window.display();
  }

  return 0;
}