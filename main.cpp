#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace sf;

int
main(int argc, char* argv[])
{
  float angle = 0.f;
  // Объект, который, собственно, является главным окном приложения
  sf::ContextSettings settings;
  // settings.antialiasingLevel = 8;
  RenderWindow window(
    VideoMode(1920, 1080), "SFML Works!", sf::Style::Fullscreen, settings);

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
  texture.setSmooth(true);
  texture.display();

  sf::Sprite sprite(texture.getTexture(),
                    IntRect(-(int)offset_W,
                            -(int)offset_H,
                            MAX_W /*+ (int)offset_W*/,
                            MAX_H /*+ (int)offset_H*/
                            ));

  // DEBUG Экспериментальный код
  sf::RenderTexture texture2;
  if (!texture2.create((int)CELL_SIZE, (int)CELL_SIZE))
    return -1;
  texture2.clear(Color::Red);
  // Обновить текстуру
  texture2.display();
  sf::Sprite sprite2(texture2.getTexture(), IntRect(50, 50, 69, 69));

  float position_x = MAX_W / 2 - 1;
  float position_y = MAX_H / 2;

  // Главный цикл приложения. Выполняется, пока открыто окно
  while (window.isOpen()) {
    // Обрабатываем очередь событий в цикле
    Event event;
    while (window.pollEvent(event)) {
      // Пользователь нажал на «крестик» и хочет закрыть окно?
      if (event.type == Event::Closed)
        // тогда закрываем его
        window.close();

      // Была ли нажата клавиша на клавиатуре?
      if (event.type == Event::KeyPressed) {
        // Вверх
        if (event.key.code == Keyboard::Up) {
          std::cout << "Press Up" << std::endl;
          if (position_y > CELL_SIZE)
            position_y -= CELL_SIZE;
        }
        // Вниз
        if (event.key.code == Keyboard::Down) {
          std::cout << "Press Down" << std::endl;
          if (position_y < MAX_H - 2 * CELL_SIZE)
            position_y += CELL_SIZE;
        }
        // Влево
        if (event.key.code == Keyboard::Left) {
          std::cout << "Press Left" << std::endl;
          if (position_x > CELL_SIZE)
            position_x -= CELL_SIZE;
        }
        // Вправо
        if (event.key.code == Keyboard::Right) {
          std::cout << "Press Right" << std::endl;
          if (position_x < MAX_W - 2 * CELL_SIZE)
            position_x += CELL_SIZE;
        }
      }
    }

    sprite2.setPosition(position_x, position_y);
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
    // line_horizontal->color = Color::Red;
    // line_vertical->color = Color::Red;
    float angleH = 15.f * 3.1419f / 180.f;
    float angleV = -5.f * 3.1419f / 180.f;

    sf::Transform tr = sf::Transform::Identity;

    sf::Transform trOrigin = sf::Transform::Identity;
    trOrigin.translate(-MAX_W / 2.f, -MAX_H / 2.f);

    sf::Transform trSkew{ 1.f, sinf(angleH), 0.f, sinf(angleV), 1.f,
                          0.f, 0.f,          0.f, 1.f };

    sf::Transform trRotate = sf::Transform::Identity;
    trRotate.rotate(angle);
    angle += 0.01;

    sf::Transform trScale = sf::Transform::Identity;
    trScale.scale(0.75f, 0.75f);

    sf::Transform trCenter = sf::Transform::Identity;
    trCenter.translate(MAX_W / 2.f, MAX_H / 2.f);

    tr = trCenter * trScale * trSkew * trOrigin;

    window.draw(sprite, tr);
    window.draw(sprite2, tr);
    // Отрисовка линии
    // window.draw(line_horizontal, 2, Lines);
    // window.draw(line_vertical, 2, Lines);
    // Отрисовка окна
    window.display();
  }

  return 0;
}