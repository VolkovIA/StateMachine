#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#pragma once
class Button
{
private:
	sf::Texture button_tex;
	sf::Texture button_texPressed;
	sf::Sprite button;

	sf::Vector2f tex_pos;
	sf::Vector2f sprite_pos;

	bool isKeyPressed = false;

public:

	// Конструкторы************************************
	Button();
	Button(sf::Vector2f pos);
	Button(std::string address, std::string address2, sf::Vector2f pos);

	// Сеттеры ****************************************

	void setImage(const std::string string1, const std::string string2);
	void setTex(int val);
	void setSpritePos(const sf::Vector2f pos);
	void setIsKeyPressed(bool value);
	
	// Геттеры ****************************************

	sf::Texture& getTex(const unsigned int value);
	sf::Sprite& getButton();
	bool getIsKeyPressed();
	
	// Другие методы***********************************

	void render(sf::RenderTarget* target);
	
	// Деструкторы*************************************
};