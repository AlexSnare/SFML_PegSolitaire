#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int
main(int argc, char* argv[])
{

  // Объект, который, собственно, является главным окном приложения
  RenderWindow window(
    VideoMode(200, 200), "SFML Works!", sf::Style::Fullscreen);

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

    window.clear(Color(250, 220, 100, 0));
    // Рисуем прямоугольник
    RectangleShape rectangle(Vector2f(1670.f, 928.f));
    // Устанавливаем ему цвет
    rectangle.setFillColor(Color(175, 180, 240));
    // Устанавливаем толщину контура круга
    rectangle.setOutlineThickness(15.f);
    // Устанавливаем цвет контура
    rectangle.setOutlineColor(Color(80, 220, 50));
    // Сместим
    rectangle.move(70, 100);
    // Отрисовка прямоугольника
    
    rectangle.getTransform();
    window.draw(rectangle);

    // Отрисовка окна
    window.display();
  }

  return 0;
}