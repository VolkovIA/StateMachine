#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime> // ��� ������� time()

int main()
{
    srand((time(NULL)));   // ���������� ��������� ���� � �������� ���������� ��������
    rand();                // ������������� Visual Studio: ������ ����� ������� ���������� ����� �� �� ������� ������������� ������� rand()

    // ������������� ����
    Game game;

    // �������� ���� ����
    while (game.running())
    {
        game.states->update();
        game.states->renderState();
    }

    return 0;
}