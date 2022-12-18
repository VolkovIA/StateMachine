#include <iostream>
#include <string>
#include <cmath>
#include "Tumbling.h"
#include "Button.h"
#pragma once
class Game;

class GameState
{
public:
	
	Game* m_game = NULL;

	virtual void update();
	virtual void renderState();
	virtual ~GameState() = default;
};



class WaitState : public GameState
{
public:

	virtual void update() override;

	WaitState();
	WaitState(Game* game_);
	~WaitState();
};



class RunState : public GameState
{
public:

	virtual void update() override;

	RunState();
	RunState(Game* game_);
	~RunState();
};



class EndState : public GameState
{
public:

	virtual void update() override;

	EndState();
	EndState(Game* game_);
	~EndState();
};

class ShowResult : public GameState
{
private:

	//bool restart = false;
	float timeShow = 0;
	int* tiles = NULL;
	int* coincidences = NULL;
	int score = 0;

	sf::Texture tex_result;
	sf::Sprite result;

	sf::FloatRect textRect;
	sf::Font font;
	sf::Text text;

public:

	virtual void update() override;
	virtual void renderState() override;
	void calculateResult();
	void textSetPos();

	ShowResult();
	ShowResult(Game* game_);
	~ShowResult();

};

class Game
{
public:

	// Настройка окна
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	const unsigned int frameRate = 120;

	// События
	sf::Event gameEvent;
	int gameStop = 0;
	bool gameStopped();

	// Таймеры и счётчики
	int currentFrame = 0; // Используется в Game для плавного разгона
	//int breaking = 0; // Используется в Game для плавной остановки
	float m_time = 0; // Таймер, начинает отсчёт после нажатия на кнопку Start
	//int tumbBreakingTime = 0; // Врeмя
	int stopTumbTime = 0; // Время, по истечении которого игра остановится и посчитает очки, равно наиболшему времени endTime в объектах Tumbling (массив tumbs)

	// Состояния

	GameState* states = nullptr; // Указатель на состояния
	GameState* temp_ptr = nullptr; // Указатель для хранения старого состояния, что бы его можно было очистить

	// Циферблаты барабанов
	const unsigned int tumbCount = 4;
	Tumbling* tumbs;

	// Кнопки меню
	Button start;
	Button stop;

	// Меню
	sf::Texture tex_menu;
	sf::Sprite menu;

	// Методы инициализации игры
	void initWindow();
	void tumbInit();
	void bottonInit();
	void menuInit();
	void initGame();

	// Движение барабанов

	float moveCoeff = 0.1;  // Коэффициент для задания величины ускорения
	float deltaMove = 0;    // Прирост смещения барабанов

	// Другие методы
	const bool running()const;
	void pollEvents();
	void gameTimer();
	void setTumblingEndTime();
	void moveTumb(Tumbling& tumb);
	void brakingTumb(Tumbling& tumb);

	// Конструкторы и деструкторы
	Game();
	~Game();
};