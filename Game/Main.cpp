#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime> // для функции time()

int main()
{
    srand((time(NULL)));   // используем системные часы в качестве стартового значения
    rand();                // пользователям Visual Studio: делаем сброс первого случайного числа из за плохого распределения функции rand()

    // Инициализация игры
    Game game;

    // Основной цикл игры
    while (game.running())
    {
        game.states->update();
        game.states->renderState();
    }

    return 0;
}