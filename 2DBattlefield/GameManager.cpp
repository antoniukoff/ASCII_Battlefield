#include "GameManager.h"

GameManager::GameManager()
{

	
}

void GameManager::playGame()
{
	level.intiMap();

	bool gameOver = false;
	while (gameOver == false) {
		level.printMap();

		level.Update();
		
		_getch();
	}
}
