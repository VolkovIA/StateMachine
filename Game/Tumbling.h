#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib> // для функций rand() и srand()
#include <string>
#pragma once
class Tumbling
{
private:
	const int tileSize = 128;
	sf::Texture tex;
	sf::Vector2f tex_pos;
	
	sf::Sprite tumb;
	sf::Vector2f sprite_pos;

	float start_coord = 0; // Случайное положение барабана в начале игры
	float endTime = 0;       // Время окончания кручения барабана - прибавляется к значению времени в момент перехода к состоянию EndState
	float current_coord = 0;  // Текущее положение барабана, для расчёта движения в Game
	int breaking = 0; // Используется в Game для плавной остановки
	float val1 = 0; // для вычисления рандомного числа endTime с плавающей точкой
	float val2 = 0; // для вычисления рандомного числа endTime с плавающей точкой
	float deltaMoveBr; // дельта для торможкения

public:
	// Конструкторы************************************

	Tumbling();
	Tumbling(sf::Vector2f pos);
	Tumbling(std::string address, sf::Vector2f pos);

	// Сеттеры ****************************************

	void setImage(const std::string string);
	void setSpritePos(const sf::Vector2f pos);
	void setStartCoord(float value);
	void setRandomEndTime(float val);
	void setEndTime(int val);
	void setCurrentCoord(float val);
	void setBreaking(int val);
	void setdeltaMoveBr(float val);

	// Геттеры ****************************************

	sf::Texture& getTex();
	sf::Sprite& getTumb();
	int getTileSize();
	float getStartCoord();
	float getEndTime();
	float getCurrentCoord();
	int getBreaking();
	float getDeltaMoveBr();

	// Другие методы и переменные**********************	

	bool isStop = true;

	//void moveTumbling(float delta);
	void render(sf::RenderTarget* target);

	// Деструкторы*************************************

	~Tumbling();
};


