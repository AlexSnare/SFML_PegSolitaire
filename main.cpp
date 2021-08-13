#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int
main(int argc, char* argv[])
{

  // Объект, который, собственно, является главным окном приложения
  RenderWindow window(VideoMode(200, 200), "SFML Works!");

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
    // Отрисовка окна
    window.display();
  }

  return 0;
}