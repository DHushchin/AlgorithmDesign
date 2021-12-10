#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "AI.hpp"

namespace Sonar
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	private:
		void InitGridPiece();
		void CheckAndPlacePieces();
		void CheckPlayerWon();
		bool CheckEmptyPieces();
		void ColorAround(int column, int row);
		void CheckGameOver();
		GameDataRef _data;
		sf::Sprite _background;
		sf::Sprite _pauseButton;
		sf::Sprite _gridSprite;
		sf::Sprite _gridPieces[8][8];
		sf::Clock _clock;
		int _gridArray[8][8];
		int gameState;
		AI* ai;
	};
}
