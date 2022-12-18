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

	// ��������� ����
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	const unsigned int frameRate = 120;

	// �������
	sf::Event gameEvent;
	int gameStop = 0;
	bool gameStopped();

	// ������� � ��������
	int currentFrame = 0; // ������������ � Game ��� �������� �������
	//int breaking = 0; // ������������ � Game ��� ������� ���������
	float m_time = 0; // ������, �������� ������ ����� ������� �� ������ Start
	//int tumbBreakingTime = 0; // ��e��
	int stopTumbTime = 0; // �����, �� ��������� �������� ���� ����������� � ��������� ����, ����� ���������� ������� endTime � �������� Tumbling (������ tumbs)

	// ���������

	GameState* states = nullptr; // ��������� �� ���������
	GameState* temp_ptr = nullptr; // ��������� ��� �������� ������� ���������, ��� �� ��� ����� ���� ��������

	// ���������� ���������
	const unsigned int tumbCount = 4;
	Tumbling* tumbs;

	// ������ ����
	Button start;
	Button stop;

	// ����
	sf::Texture tex_menu;
	sf::Sprite menu;

	// ������ ������������� ����
	void initWindow();
	void tumbInit();
	void bottonInit();
	void menuInit();
	void initGame();

	// �������� ���������

	float moveCoeff = 0.1;  // ����������� ��� ������� �������� ���������
	float deltaMove = 0;    // ������� �������� ���������

	// ������ ������
	const bool running()const;
	void pollEvents();
	void gameTimer();
	void setTumblingEndTime();
	void moveTumb(Tumbling& tumb);
	void brakingTumb(Tumbling& tumb);

	// ������������ � �����������
	Game();
	~Game();
};