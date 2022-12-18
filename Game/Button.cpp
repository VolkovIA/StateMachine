#include "Button.h"

// Конструкторы************************************

Button::Button()
{
	button.setTexture(button_tex);
	button.setPosition(0.f, 0.f);
}

Button::Button(sf::Vector2f pos)
{
	button.setTexture(button_tex);
	button.setPosition(pos);
}

Button::Button(std::string address, std::string address2, sf::Vector2f pos)
{
	button_tex.loadFromFile(address);
	button_texPressed.loadFromFile(address2);
	button.setTexture(button_tex);
	button.setPosition(pos);
}

// Сеттеры ****************************************

void Button::setImage(const std::string string1, const std::string string2)
{
	button_tex.loadFromFile(string1);
	button_texPressed.loadFromFile(string2);
}

void Button::setTex(int val)
{
	if (val == 0)
	{
		button.setTexture(button_tex);
	}
	else if (val == 1)
	{
		button.setTexture(button_texPressed);
	}
}

void Button::setSpritePos(const sf::Vector2f pos)
{
	button.setPosition(pos);
}

void Button::setIsKeyPressed(bool value)
{
	isKeyPressed = value;
}

// Геттеры ****************************************

sf::Texture& Button::getTex(const unsigned int value)
{
	if (value == 0)
	{
		return button_tex;
	}
	else if (value == 1)
	{
		return button_texPressed;
	}
}

sf::Sprite& Button::getButton()
{
	return button;
}

bool Button::getIsKeyPressed()
{
	return isKeyPressed;
}

// Другие методы***********************************

void Button::render(sf::RenderTarget* target)
{
	target->draw(button);
}