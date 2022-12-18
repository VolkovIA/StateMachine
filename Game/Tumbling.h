#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib> // ��� ������� rand() � srand()
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

	float start_coord = 0; // ��������� ��������� �������� � ������ ����
	float endTime = 0;       // ����� ��������� �������� �������� - ������������ � �������� ������� � ������ �������� � ��������� EndState
	float current_coord = 0;  // ������� ��������� ��������, ��� ������� �������� � Game
	int breaking = 0; // ������������ � Game ��� ������� ���������
	float val1 = 0; // ��� ���������� ���������� ����� endTime � ��������� ������
	float val2 = 0; // ��� ���������� ���������� ����� endTime � ��������� ������
	float deltaMoveBr; // ������ ��� �����������

public:
	// ������������************************************

	Tumbling();
	Tumbling(sf::Vector2f pos);
	Tumbling(std::string address, sf::Vector2f pos);

	// ������� ****************************************

	void setImage(const std::string string);
	void setSpritePos(const sf::Vector2f pos);
	void setStartCoord(float value);
	void setRandomEndTime(float val);
	void setEndTime(int val);
	void setCurrentCoord(float val);
	void setBreaking(int val);
	void setdeltaMoveBr(float val);

	// ������� ****************************************

	sf::Texture& getTex();
	sf::Sprite& getTumb();
	int getTileSize();
	float getStartCoord();
	float getEndTime();
	float getCurrentCoord();
	int getBreaking();
	float getDeltaMoveBr();

	// ������ ������ � ����������**********************	

	bool isStop = true;

	//void moveTumbling(float delta);
	void render(sf::RenderTarget* target);

	// �����������*************************************

	~Tumbling();
};


