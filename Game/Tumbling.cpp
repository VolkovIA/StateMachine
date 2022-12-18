#include "Tumbling.h"

// Конструкторы************************************

Tumbling::Tumbling()
{
	start_coord = tileSize * (rand() % 4);
	tumb.setTexture(tex);
	tumb.setTextureRect(sf::IntRect(0.f, start_coord, tileSize, tileSize));
	tumb.setPosition(0.f, 0.f);
	current_coord = start_coord;
	//std::cout << "tumb start coord: " << start_coord << '\n';
}

Tumbling::Tumbling(sf::Vector2f pos)
{
	start_coord = tileSize * (rand() % 4);
	tumb.setTexture(tex);
	tumb.setTextureRect(sf::IntRect(0.f, start_coord, tileSize, tileSize));
	tumb.setPosition(pos);
	current_coord = start_coord;
}

Tumbling::Tumbling(std::string address, sf::Vector2f pos)
{
	start_coord = tileSize * (rand() % 4);
	tex.loadFromFile(address);
	tumb.setTexture(tex);
	tumb.setTextureRect(sf::IntRect(0.f, start_coord, tileSize, tileSize));
	tumb.setPosition(pos);
	current_coord = start_coord;
}

// Сеттеры ****************************************

void Tumbling::setImage(const std::string string)
{
	tex.loadFromFile(string);
}

void Tumbling::setSpritePos(const sf::Vector2f pos)
{
	tumb.setPosition(pos);
}

void Tumbling::setStartCoord(float value)
{
	start_coord = value;
}

void Tumbling::setRandomEndTime(float val)
{
	val1 = rand() % 5 + 5;
	val2 = rand() % 4 + 1;
	endTime = val + val1 / val2;
	/*std::cout << "val1: " << val1 << '\n';
	std::cout << "val2: " << val2 << '\n';
	std::cout << "val: " << val << '\n';
	std::cout << "endTime " << val <<" + " << val1 / val2 << " = " << endTime << '\n';*/
}

void Tumbling::setEndTime(int val)
{
	endTime = val;
}

void Tumbling::setCurrentCoord(float val)
{
	if (tex.getSize().y - tileSize > val)
	{
		current_coord = val;
	}
	else
	{
		current_coord = val - current_coord;
	}
}

void Tumbling::setBreaking(int val)
{
	if (val >= 0)
	{
		breaking = val;
		//std::cout << "breaking: " << breaking << '\n';
	}
	else
	{
		breaking = 0;
	}
}

void Tumbling::setdeltaMoveBr(float val)
{
	deltaMoveBr = val; // Используется для торможения барабанов
}

// Геттеры ****************************************

sf::Texture& Tumbling::getTex()
{
	return tex;
}

sf::Sprite& Tumbling::getTumb()
{
	return tumb;
}

int Tumbling::getTileSize()
{
	return tileSize;
}

float Tumbling::getStartCoord()
{
	return start_coord;
}

float Tumbling::getEndTime()
{
	return endTime;
}

float Tumbling::getCurrentCoord()
{
	return current_coord;
}

int Tumbling::getBreaking()
{
	return breaking;
}

float Tumbling::getDeltaMoveBr()
{
	return deltaMoveBr;
}

// Другие методы***********************************

//void Tumbling::moveTumbling(float delta)
//{
//	this->tumb.setTextureRect(sf::IntRect(0.f, this->start_coord, this->tileSize, this->tileSize));
//}

void Tumbling::render(sf::RenderTarget* target)
{
	target->draw(tumb);
}

// Деструкторы*************************************

Tumbling::~Tumbling(){}
