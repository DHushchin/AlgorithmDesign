#include <sstream>
#include <iostream>
#include "GameState.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"
#include "DEFINITIONS.hpp"


namespace Sonar
{
	GameState::GameState(GameDataRef data)
	{
		this->_data = data;
	}

	void GameState::Init()
	{
		gameState = STATE_PLAYING;

		this->ai = new AI(this->_data);
		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		this->_data->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Piece", O_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("Block Piece", BLOCK_PIECE);

		_background.setTexture(this->_data->assets.GetTexture("Background"));
		_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		_gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));
		_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getGlobalBounds().width + 5, _pauseButton.getPosition().y + 13);
		_gridSprite.setPosition(SCREEN_WIDTH / 2 - _gridSprite.getGlobalBounds().width / 2 - 50, SCREEN_HEIGHT / 2 - _gridSprite.getGlobalBounds().height / 2);
		InitGridPiece();
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				_gridArray[x][y] = EMPTY_PIECE;
			}
		}
	}

	void GameState::HandleInput()
	{
		sf::Event event;
		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (this->_data->input.isSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
			}
			else if (this->_data->input.isSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window))
			{
				this->CheckAndPlacePieces();
			}
		}
	}

	void GameState::Update(float dt)
	{
		if (gameState == STATE_LOSE || gameState == STATE_WON)
		{
			if (this->_clock.getElapsedTime().asSeconds() > TIME_BEFORE_SHOWING_GAME_OVER)
			{
				this->_data->machine.AddState(StateRef(new GameOverState(_data, gameState)), true);
			}
		}
	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear();
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_pauseButton);
		this->_data->window.draw(this->_gridSprite);

		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				this->_data->window.draw(this->_gridPieces[x][y]);
			}
		}

		this->_data->window.display();
	}

	void GameState::InitGridPiece()
	{
		sf::Vector2u tempSpriteSize = this->_data->assets.GetTexture("X Piece").getSize();
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				_gridPieces[x][y].setTexture(this->_data->assets.GetTexture("X Piece"));
				_gridPieces[x][y].setPosition(_gridSprite.getPosition().x + tempSpriteSize.x * x, 
					                          _gridSprite.getPosition().y + tempSpriteSize.y * y);
				_gridPieces[x][y].setColor(sf::Color(255, 255, 255, 0));
			}
		}
	}

	void GameState::CheckAndPlacePieces()
	{
		sf::Vector2i touchPoint = this->_data->input.GetMousePosition(this->_data->window);
		sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
		sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2 - 50, (SCREEN_HEIGHT - gridSize.height) / 2);
		sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);
		sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 8, gridSize.height / 8);
		int column = 0, row = 0;

		for (int i = 1; i <= 8; i++)
		{
			if (gridLocalTouchPos.x < gridSectionSize.x * i)
			{
				column = i - 1;
				break;
			}
		}

		for (int j = 1; j <= 8; j++)
		{
			if (gridLocalTouchPos.y < gridSectionSize.y * j)
			{
				row = j - 1;
				break;
			}
		}
		
		if (_gridArray[column][row] == EMPTY_PIECE)
		{

			_gridPieces[column][row].setTexture(this->_data->assets.GetTexture("X Piece"));
			_gridArray[column][row] = BLOCKED_PIECE;
			this->ColorAround(column, row);
			gameState = STATE_AI_PLAYING;
			this->CheckPlayerWon();
		}
	}

	void GameState::CheckPlayerWon()
	{
		CheckGameOver();
		
		if (gameState == STATE_AI_PLAYING)
		{
			int col = -1, row = -1;

			int tempGrid[8][8];
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					tempGrid[i][j] = this->_gridArray[i][j];
				}
			}
			
			ai->PlacePiece(tempGrid, col, row);

			gameState = STATE_PLAYING;

			this->_gridArray[col][row] = BLOCKED_PIECE;
			this->ColorAround(col, row);
			this->_gridPieces[col][row].setTexture(this->_data->assets.GetTexture("O Piece"));
			CheckGameOver();
		}
	}

	void GameState::CheckGameOver()
	{
		if (!this->CheckEmptyPieces())
		{
			if (this->gameState == STATE_PLAYING)
			{
				gameState = STATE_LOSE;
			}
			else
			{
				gameState = STATE_WON;
			}

			this->_clock.restart();
		}
	}

	bool GameState::CheckEmptyPieces()
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (this->_gridArray[i][j] != BLOCKED_PIECE)
				{
					return true;
				}
			}
		}
		return false;
	}

	void GameState::ColorAround(int c, int r)
	{
		for (int i = c - 1; i < c + 2; i++)
		{
			for (int j = r - 1; j < r + 2; j++)
			{
				if (i >= 0 && i <= 7 && j >= 0 && j <= 7)
				{
					this->_gridPieces[i][j].setColor(sf::Color(255, 255, 255, 255));
					this->_gridArray[i][j] = BLOCKED_PIECE;
					if (i == c && j == r)
					{
						continue;
					}
					this->_gridPieces[i][j].setTexture(this->_data->assets.GetTexture("Block Piece"));

				}
			}
		}
	}

}

