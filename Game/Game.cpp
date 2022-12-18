#include "Game.h"

// Методы Инициализации игры*************************************************
void Game::initWindow() // Метод инициализации окна
{
	videoMode = sf::VideoMode(1200, 800);
	window = new sf::RenderWindow(videoMode, "MyGame", 7U, sf::ContextSettings(0, 0, 8));
	window->setFramerateLimit(frameRate);
}

void Game::tumbInit() // Метод инициализации барабнов и их позиции
{
	tumbs[0].setSpritePos(sf::Vector2f(154.f, 326.f));
	tumbs[0].getTex().loadFromFile("images/Symbols.png");
	tumbs[0].getTumb().setTexture(tumbs[0].getTex(), true);
	tumbs[0].getTumb().setTextureRect(sf::IntRect(0.f, tumbs[0].getStartCoord(), tumbs[0].getTileSize(), tumbs[0].getTileSize())); // обновление TextureRect

	tumbs[1].setSpritePos(sf::Vector2f(294.f, 326.f));
	tumbs[1].getTex().loadFromFile("images/Symbols.png");
	tumbs[1].getTumb().setTexture(tumbs[1].getTex(), true);
	tumbs[1].getTumb().setTextureRect(sf::IntRect(0.f, tumbs[1].getStartCoord(), tumbs[1].getTileSize(), tumbs[1].getTileSize()));

	tumbs[2].setSpritePos(sf::Vector2f(435.f, 326.f));
	tumbs[2].getTex().loadFromFile("images/Symbols.png");
	tumbs[2].getTumb().setTexture(tumbs[2].getTex(), true);
	tumbs[2].getTumb().setTextureRect(sf::IntRect(0.f, tumbs[2].getStartCoord(), tumbs[2].getTileSize(), tumbs[2].getTileSize()));

	tumbs[3].setSpritePos(sf::Vector2f(575.f, 326.f));
	tumbs[3].getTex().loadFromFile("images/Symbols.png");
	tumbs[3].getTumb().setTexture(tumbs[3].getTex(), true);
	tumbs[3].getTumb().setTextureRect(sf::IntRect(0.f, tumbs[3].getStartCoord(), tumbs[3].getTileSize(), tumbs[3].getTileSize()));
}

void Game::bottonInit() // Метод инициализации кнопок
{
	start.setSpritePos(sf::Vector2f(822.f, 148.f));
	start.setImage("images/Start_Up.png", "images/Start_Down.png");
	start.getButton().setTexture(start.getTex(0), true); // обновление texture в спрайте

	stop.setSpritePos(sf::Vector2f(822.f, 547.f));
	stop.setImage("images/Stop_Up.png", "images/Stop_Down.png");
	stop.getButton().setTexture(stop.getTex(0), true);
}

void Game::menuInit() // Метод инициализации меню
{
	tex_menu.loadFromFile("images/Menu.png");
	menu.setTexture(tex_menu);
}

void Game::initGame() // Инициализация окна и игровых элементов
{
	tumbs = new Tumbling[tumbCount];
	initWindow();
	tumbInit();
	bottonInit();
	menuInit();
}

// События************************************************************

bool Game::gameStopped()
{
	if (gameStop == tumbCount)
	{
		//std::cout << "Game stopped" << '\n';
		return true;
	}
	else
	{
		return false;
	}
}

// Другие методы *****************************************************

const bool Game::running()const
{
	return window->isOpen();
}

void Game::pollEvents()
{
	while (window->pollEvent(gameEvent)) // Обработка событий
	{
		if (gameEvent.type == sf::Event::Closed)
			window->close();
	}
}

void Game::gameTimer()
{
	currentFrame += 1;

	if (!(currentFrame % (frameRate/10)))
	{
		m_time += 0.1;
		//std::cout << "Time: " << m_time << '\n';
	}
}

void Game::setTumblingEndTime()
{
	//std::cout << "setTumblingEndTime called" << '\n';
	for (int i = 0; i < tumbCount; ++i)
	{
		//std::cout << "time: " << m_time << '\n';
		tumbs[i].setRandomEndTime(m_time);

		//endGameTime = (endGameTime < tumbs[i].getEndTime()) ? tumbs[i].getEndTime() : endGameTime; // Время остановки последнего барабана

		//std::cout << "*******************************************" << '\n';
	}
}

void Game::moveTumb(Tumbling& tumb)
{
	if (m_time <= 1)
	{
		deltaMove = currentFrame * moveCoeff;

		//std::cout << "deltaMove: " << deltaMove << '\n';

		tumb.setCurrentCoord(tumb.getCurrentCoord() + deltaMove);
		tumb.getTumb().setTextureRect(sf::IntRect(0.f, tumb.getCurrentCoord(), tumb.getTileSize(), tumb.getTileSize()));
		tumb.setBreaking(currentFrame);
	}
	else if (m_time > 1)
	{
		//std::cout << "deltaMove: " << deltaMove << '\n';
		tumb.setCurrentCoord(tumb.getCurrentCoord() + deltaMove);
		tumb.getTumb().setTextureRect(sf::IntRect(0.f, tumb.getCurrentCoord(), tumb.getTileSize(), tumb.getTileSize()));
	}
}

void Game::brakingTumb(Tumbling& tumb)
{
	//std::cout << "brakingTumb called." << '\n';

	tumb.setdeltaMoveBr(tumb.getBreaking() * moveCoeff);
	//std::cout << "deltaMove breaking: " << tumb.getDeltaMoveBr() << '\n';
	
	if (tumb.getBreaking() > 1)
	{
		tumb.setCurrentCoord(tumb.getCurrentCoord() + tumb.getDeltaMoveBr());
		tumb.getTumb().setTextureRect(sf::IntRect(0.f, tumb.getCurrentCoord(), tumb.getTileSize(), tumb.getTileSize()));
		tumb.setBreaking(tumb.getBreaking() - 1);
	}
	else if ((tumb.getBreaking() <= 1 && static_cast<int>(fmod(tumb.getCurrentCoord(), 128)))/* || (tumb.getBreaking() <= 1 && tumb.getCurrentCoord() < 128)*/)
	{
		tumb.setCurrentCoord(tumb.getCurrentCoord() + tumb.getDeltaMoveBr());
		tumb.getTumb().setTextureRect(sf::IntRect(0.f, tumb.getCurrentCoord(), tumb.getTileSize(), tumb.getTileSize()));
	}
	else if (!tumb.isStop)
	{
		//std::cout << "Tumb stopped************************" << '\n';
		tumb.isStop = true;
		++gameStop;
		//std::cout << "gameStop: " << gameStop << '\n';
	}
}

//void Game::setGamePtr(Game* ptr)
//{
//	game_ptr = ptr;
//}

// Конструкторы и деструкторы*****************************************

Game::Game()
{
	this->initGame();
	states = new WaitState(this);
}

Game::~Game()
{
	delete[]tumbs;
	delete states;
	delete window;
}

// Состояния ********************************************************************
// IGameState*********************************************************

void GameState::update(){}

void GameState::renderState()
{
	m_game->window->clear(sf::Color(225.f, 225.f, 225.f));

	m_game->window->draw(m_game->menu);

	for (int i = 0; i < m_game->tumbCount; ++i)
	{
		m_game->tumbs[i].render(m_game->window);
	}

	m_game->start.render(m_game->window);
	m_game->stop.render(m_game->window);

	m_game->window->display();
}

// WaitState**********************************************************

WaitState::WaitState(){}

WaitState::WaitState(Game* game_)
{
	m_game = game_;
	m_game->currentFrame = 0;
	m_game->gameStop = 0;
	m_game->m_time = 0;
	m_game->gameStop = 0;
	//m_game->tumbBreakingTime = 0;
	m_game->stopTumbTime = 0;
}

void WaitState::update()
{
	//std::cout << "WaitState::update()" << '\n';

	if (m_game->temp_ptr)
	{
		delete m_game->temp_ptr;
		m_game->temp_ptr = nullptr;
	}

	while (m_game->window->pollEvent(m_game->gameEvent)) // Обработка событий
	{
		if (m_game->gameEvent.type == sf::Event::Closed)
			m_game->window->close();

		if (m_game->gameEvent.type == sf::Event::MouseButtonPressed)
		{
			if (m_game->gameEvent.mouseButton.button == sf::Mouse::Left)
			{
				//std::cout << "Key is pressed" << '\n';
				if (m_game->start.getButton().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*(m_game->window)))))
				{
					m_game->start.setTex(1);
					m_game->start.setIsKeyPressed(true);
				}

				if (m_game->stop.getButton().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*(m_game->window)))))
				{
					m_game->stop.setTex(1);
					m_game->stop.setIsKeyPressed(true);
				}
			}
		}
		if (m_game->gameEvent.type == sf::Event::MouseButtonReleased)
		{
			if (m_game->gameEvent.mouseButton.button == sf::Mouse::Left)
			{
				if (m_game->start.getIsKeyPressed())
				{
					m_game->start.setTex(0);
					m_game->start.setIsKeyPressed(false);

					for (int i = 0; i < m_game->tumbCount; ++i)
					{
						m_game->tumbs[i].isStop = true;
					}

					m_game->temp_ptr = m_game->states;
					//std::cout << "temp_ptr: " << m_game->temp_ptr << ", states: " << m_game->states << '\n';
					m_game->states = new RunState(m_game);
				}

				if (m_game->stop.getIsKeyPressed())
				{
					m_game->stop.setTex(0);
					m_game->stop.setIsKeyPressed(false);
				}
			}
		}
	}

	// Анимация кнопок
	/*if (game->start.getIsKeyPressed())
	{
		game->start.setTex(0);
		game->start.setIsKeyPressed(false);
		
		if (game->temp_ptr)
		{
			delete game->temp_ptr;
		}

		game->temp_ptr = game->states;
		game->states = new RunState(game);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		std::cout << "Key is pressed" << '\n';
		if (game->start.getButton().getGlobalBounds().contains(sf::Mouse::getPosition(*(game->window)).x, sf::Mouse::getPosition(*(game->window)).y))
		{
			game->start.setTex(1);
			game->start.setIsKeyPressed(true);
		}
	}

	if (game->stop.getIsKeyPressed())
	{
		game->stop.setTex(0);
		game->stop.setIsKeyPressed(false);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (game->stop.getButton().getGlobalBounds().contains(sf::Mouse::getPosition(*(game->window)).x, sf::Mouse::getPosition(*(game->window)).y))
		{
			game->stop.setTex(1);
			game->stop.setIsKeyPressed(true);
		}
	}*/
}

WaitState::~WaitState()
{
	//std::cout << "~WaitState()" << '\n';
}

// RuntState**********************************************************

RunState::RunState(){}

RunState::RunState(Game* game_)
{
	m_game = game_;

	for (int i = 0; i < m_game->tumbCount; ++i)
	{
		m_game->tumbs[i].isStop = false;
	}
}

void RunState::update()
{
	//std::cout << "RuntState::update()" << '\n';

	if (m_game->temp_ptr)
	{
		delete m_game->temp_ptr;
		m_game->temp_ptr = nullptr;
	}

	while (m_game->window->pollEvent(m_game->gameEvent)) // Обработка событий
	{
		if (m_game->gameEvent.type == sf::Event::Closed)
			m_game->window->close();

		if (m_game->gameEvent.type == sf::Event::MouseButtonPressed)
		{
			if (m_game->gameEvent.mouseButton.button == sf::Mouse::Left)
			{
				//std::cout << "Key is pressed" << '\n';
				if (m_game->start.getButton().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*(m_game->window)))))
				{
					m_game->start.setTex(1);
					m_game->start.setIsKeyPressed(true);
				}

				if (m_game->stop.getButton().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*(m_game->window)))))
				{
					m_game->stop.setTex(1);
					m_game->stop.setIsKeyPressed(true);
				}
			}
		}
		if (m_game->gameEvent.type == sf::Event::MouseButtonReleased)
		{
			if (m_game->gameEvent.mouseButton.button == sf::Mouse::Left)
			{
				if (m_game->start.getIsKeyPressed())
				{
					m_game->start.setTex(0);
					m_game->start.setIsKeyPressed(false);
				}

				if (m_game->stop.getIsKeyPressed())
				{
					m_game->stop.setTex(0);
					m_game->stop.setIsKeyPressed(false);

					m_game->temp_ptr = m_game->states;
					//std::cout << "temp_ptr: " << m_game->temp_ptr << ", states: " << m_game->states << '\n';
					m_game->states = new EndState(m_game);
				}
			}
		}
	}

	if (m_game->m_time > 5)
	{
		m_game->temp_ptr = m_game->states;
		//std::cout << "gameTime > 6, temp_ptr: " << m_game->temp_ptr << ", states: " << m_game->states << '\n';
		m_game->states = new EndState(m_game);
	}

	m_game->gameTimer();
	for (int i = 0; i < m_game->tumbCount; ++i)
	{
		m_game->moveTumb(m_game->tumbs[i]);
	}
}

RunState::~RunState()
{
	//std::cout << "~RunState()" << '\n';
}

// EndState***********************************************************

EndState::EndState(){}

EndState::EndState(Game* game_)
{
	m_game = game_;

	// Устанавливает отрезко времени, который прибавляется к текущему времени для каждого барабана,
	// после того, как время становится больше этой величины, барабаны начинают тормозить
	m_game->setTumblingEndTime();
	//std::cout << "tumbBreakingTime: " << game->tumbBreakingTime << '\n';
	//m_game->tumbBreakingTime = m_game->m_time;
	for (int i = 0; i < m_game->tumbCount; ++i)
	{
		m_game->tumbs[i].setdeltaMoveBr(m_game->deltaMove);
	}
}

void EndState::update()
{
	//std::cout << "EndState::update()" << '\n';

	if (m_game->temp_ptr)
	{
		delete m_game->temp_ptr;
		m_game->temp_ptr = nullptr;
	}

	while (m_game->window->pollEvent(m_game->gameEvent)) // Обработка событий
	{
		if (m_game->gameEvent.type == sf::Event::Closed)
			m_game->window->close();
	}

	if (!m_game->gameStopped())
	{
		for (int i = 0; i < m_game->tumbCount; ++i)
		{
			if ((m_game->tumbs[i].getEndTime()/* + m_game->tumbBreakingTime*/) > m_game->m_time)
			{
				m_game->moveTumb(m_game->tumbs[i]);
			}
			else if (m_game->gameStop < m_game->tumbCount)
			{
				m_game->brakingTumb(m_game->tumbs[i]);
			}
		}
	}
	else
	{
		//m_game->tumbBreakingTime = 0;
		m_game->temp_ptr = m_game->states;
		//std::cout << "temp_ptr: " << m_game->temp_ptr << ", states: " << m_game->states << '\n';
		m_game->states = new ShowResult(m_game);
	}

	m_game->gameTimer();
}

EndState::~EndState()
{
	//std::cout << "~EndState()" << '\n';
}

// Состояние показывает количество набранных очков

ShowResult::ShowResult(){}

ShowResult::ShowResult(Game* game_)
{
	m_game = game_;

	tex_result.loadFromFile("images/Score.png");
	result.setTexture(tex_result);
	result.setPosition(sf::Vector2f(425.f, 300.f));

	font.loadFromFile("timesbd.ttf");
	text.setPosition(sf::Vector2f(600.f, 400.f));
	text.setFont(font);
	text.setCharacterSize(25);
	text.setString("Game over, your score is ");
	text.setFillColor(sf::Color::Black);

	timeShow = m_game->m_time + 3.0f; // Время показа финального сообщения
	tiles = new int[m_game->tumbCount]{0}; // Сюда записываю координаты текстур в барабанах, после их остановки для рассчёта очков
	coincidences = new int[m_game->tumbCount + 1]{0}; // Сюда записываю сколько символов на барабанах совпадают

	calculateResult();
	textSetPos();
}

void ShowResult::update()
{
	//std::cout << "ShowResult::update()" << '\n';

	if (m_game->temp_ptr)
	{
		delete m_game->temp_ptr;
		m_game->temp_ptr = nullptr;
	}

	// Обработка событий
	while (m_game->window->pollEvent(m_game->gameEvent)) 
	{
		if (m_game->gameEvent.type == sf::Event::Closed)
			m_game->window->close();

		// Кнопки
		if (m_game->gameEvent.type == sf::Event::MouseButtonPressed)
		{
			if (m_game->gameEvent.mouseButton.button == sf::Mouse::Left)
			{
				//std::cout << "Key is pressed" << '\n';
				if (m_game->start.getButton().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*(m_game->window)))))
				{
					m_game->start.setTex(1);
					m_game->start.setIsKeyPressed(true);
				}

				if (m_game->stop.getButton().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*(m_game->window)))))
				{
					m_game->stop.setTex(1);
					m_game->stop.setIsKeyPressed(true);
				}
			}
		}
		if (m_game->gameEvent.type == sf::Event::MouseButtonReleased)
		{
			if (m_game->gameEvent.mouseButton.button == sf::Mouse::Left)
			{
				if (m_game->start.getIsKeyPressed())
				{
					m_game->start.setTex(0);
					m_game->start.setIsKeyPressed(false);
				}

				if (m_game->stop.getIsKeyPressed())
				{
					m_game->stop.setTex(0);
					m_game->stop.setIsKeyPressed(false);
				}
			}
		}
	}

	if (m_game->m_time > timeShow)
	{
		timeShow = 0;
		score = 0;

		m_game->temp_ptr = m_game->states;
		//std::cout << "temp_ptr: " << m_game->temp_ptr << ", states: " << m_game->states << '\n';
		m_game->states = new WaitState(m_game);
	}

	m_game->gameTimer();
}

void ShowResult::renderState()
{
	m_game->window->clear(sf::Color(225.f, 225.f, 225.f));
	m_game->window->draw(m_game->menu);

	for (int i = 0; i < m_game->tumbCount; ++i)
	{
		m_game->tumbs[i].render(m_game->window);
	}

	m_game->start.render(m_game->window);
	m_game->stop.render(m_game->window);
	m_game->window->draw(result);
	m_game->window->draw(text);
	m_game->window->display();
}

void ShowResult::calculateResult()
{
	for (int i = 0; i < m_game->tumbCount; ++i)
	{
		if (m_game->tumbs[i].getCurrentCoord() < 128)
		{
			tiles[i] = 1;
		}
		else if (m_game->tumbs[i].getCurrentCoord() >= 128 && m_game->tumbs[i].getCurrentCoord() < 256)
		{
			tiles[i] = 2;
		}
		else if (m_game->tumbs[i].getCurrentCoord() >= 256 && m_game->tumbs[i].getCurrentCoord() < 384)
		{
			tiles[i] = 3;
		}
		else if (m_game->tumbs[i].getCurrentCoord() >= 384 && m_game->tumbs[i].getCurrentCoord() < 512)
		{
			tiles[i] = 4;
		}
		//std::cout << "tumb " << i << " - score " << tiles[i] << '\n';
	}

	for (int i = 0; i < m_game->tumbCount + 1; ++i)
	{
		for (int j = 0; j < m_game->tumbCount; ++j)
		{
			if (i == tiles[j])
			{
				coincidences[i] += 1;
			}
		}
		//std::cout << "score " << i << ", coincidences " << coincidences[i] << '\n';
	}

	for (int i = 0; i < m_game->tumbCount + 1; ++i)
	{
		if (coincidences[i] != 0)
		{
			score += i * coincidences[i];
		}
	}
	//std::cout << "Total score is " << score << '\n';
}

void ShowResult::textSetPos()
{
	text.setString("Game over, your score is " + std::to_string(score));
	textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(1200 / 2.0f, 800 / 2.0f));
}

ShowResult::~ShowResult()
{
	//std::cout << "~ShowResulat()" << '\n';
	delete[] tiles;
	delete[] coincidences;
}