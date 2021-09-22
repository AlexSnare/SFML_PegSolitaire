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

  sf::Vector2u permission = window.getSize();
  int MAX_W = permission.x;
  int MAX_H = permission.y;

  float CELL_SIZE = 70.0f;

  lines.append(sf::Vertex(sf::Vector2f(0.0f, CELL_SIZE - 1), Color::White));
  lines.append(
    sf::Vertex(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1), Color::White));
  lines.append(sf::Vertex(sf::Vector2f(CELL_SIZE - 1, 0.0f), Color::White));

  float offset_W = (float)((MAX_W / 2) % (int)CELL_SIZE);
  float offset_H = (float)((MAX_H / 2) % (int)CELL_SIZE);

  std::cout << "offset_h = " << (int)offset_W << std::endl;
  std::cout << "offset_w = " << (int)offset_H << std::endl;

  sf::RenderTexture texture;
  if (!texture.create((int)CELL_SIZE, (int)CELL_SIZE))
    return -1;

  texture.clear(Color::Blue);
  texture.draw(lines);
  texture.setRepeated(true);
  texture.display();

  sf::Sprite sprite(texture.getTexture(),
                    IntRect(-(int)offset_W,
                            -(int)offset_H,
                            MAX_W + (int)offset_W,
                            MAX_H + (int)offset_H));

  // DEBUG Экспериментальный код
  sf::RenderTexture texture2;
  if (!texture2.create((int)CELL_SIZE, (int)CELL_SIZE))
    return -1;
  texture2.clear(Color::Red);
  // Обновить текстуру
  texture2.display();
  sf::Sprite sprite2(texture2.getTexture(), IntRect(50, 50, 70, 70));
  sprite2.setPosition((int)(MAX_W / 2 - 1), (int)(MAX_H / 2 - 1));
  //

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

    Vertex line_horizontal[] = {
      // Координата первой вершины
      Vertex(Vector2f(0.0f, (float)(MAX_H / 2))),
      // Координата второй вершины
      Vertex(Vector2f((float)MAX_W, (float)(MAX_H / 2)))
    };
    Vertex line_vertical[] = {
      // Координата первой вершины
      Vertex(Vector2f((float)(MAX_W / 2), 0.0f)),
      // Координата второй вершины
      Vertex(Vector2f((float)(MAX_W / 2), (float)(MAX_H)))
    };

    // Устанавливаем цвет линии - красный
    line_horizontal->color = Color::Red;
    line_vertical->color = Color::Red;

    window.draw(sprite);
    window.draw(sprite2);
    // Отрисовка линии
    window.draw(line_horizontal, 2, Lines);
    window.draw(line_vertical, 2, Lines);
    // Отрисовка окна
    window.display();
  }

  return 0;
}