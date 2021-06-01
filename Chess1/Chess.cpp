#include <SFML/Graphics.hpp>
#include <iostream>
#include "Chess.h"
#include <vector>

using namespace sf;

Chess::Chess()
{
	window.create(VideoMode(800, 800), "Chess");

	t1.loadFromFile("images/board.png");
	t2.loadFromFile("images/PionNegru.png");
	t3.loadFromFile("images/PionAlb.png");
	t4.loadFromFile("images/youwin.png");
	t5.loadFromFile("images/GameOver.png");

	Plank.setTexture(t1);
	PawnBl.setTexture(t2);
	PawnWh.setTexture(t3);
	GameOverBlack.setTexture(t4);
	GameOverWhite.setTexture(t5);
	GameOverWhite.setPosition(136, 136);
	GameOverBlack.setPosition(160, 260);


}

void Chess::StartGame()
{
	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);
		x = pos.x / width;
		y = pos.y / height;
		


		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}

			if (e.type == Event::Resized)
			{
				height = e.size.height / 8;
				width = e.size.width / 8;
			}

			checkingEndGame();

			mouseButtonPressedOnPawn(pos);

			movePawnAI();

			mouseButtonReleasedOnPawn(pos);
		}
		renderingSprites(pos);
		window.display();
	}

}

//movement for pawns
int Chess::pawnMovement(int currentX, int currentY, int newX, int newY)
{
	//up
	if (newY == currentY - 1 && newX == currentX && board[currentY - 1][currentX] == 0)
	{
		return 1;
	}
	//down
	if (newY == currentY + 1 && newX == currentX && board[currentY + 1][currentX] == 0)
	{
		return 1;
	}
	//left
	if (newY == currentY && newX == currentX - 1 && board[currentY][currentX - 1] == 0)
	{
		return 1;
	}
	//right
	if (newY == currentY && newX == currentX + 1 && board[currentY][currentX + 1] == 0)
	{
		return 1;
	}
	return 0;
}

//Check for white victory
int Chess::checkWinnerWhite()
{
	int result = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == -1)
			{
				result++;
			}
		}
	}
	if (result == 9)
		return 1;
	return 0;
}

int Chess::checkWinnerBlack()
{
	int result = 0;
	for (int i = 5; i < 8; i++)
	{
		for (int j = 5; j < 8; j++)
		{
			if (board[j][i] == 1)
			{
				result++;
			}
		}
	}
	if (result == 9)
		return 1;
	return 0;
}

void Chess::defoltBoard()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (j < 3 && i < 3)
			{
				board[j][i] = 1;
			}
			else if (j > 4 && i > 4)
			{
				board[j][i] = -1;
			}
			else
			{
				board[j][i] = 0;
			}
		}
	}
}

void Chess::checkingEndGame()
{
	if (checkWinnerWhite())
	{
		travel = 2; //Blocking movement
		gameOver = 1;

		if (e.type == Event::MouseButtonPressed)
		{
			if (e.key.code == Mouse::Left)
			{
				defoltBoard();
				travel = 0;
				gameOver = 0;
			}
		}
	}

	if (checkWinnerBlack())
	{
		travel = 2; //Blocking movement
		gameOver = 2;

		if (e.type == Event::MouseButtonPressed)
		{
			if (e.key.code == Mouse::Left)
			{
				defoltBoard();
				travel = 0;
				gameOver = 0;
			}
		}
	}
}

void Chess::mouseButtonPressedOnPawn(Vector2i pos)
{
	if (e.type == Event::MouseButtonPressed)
	{
		if (e.key.code == Mouse::Left)
		{
			if (board[y][x] != 0)
			{
				dx = pos.x - x * 100;
				dy = pos.y - y * 100;


				if (board[y][x] == PawnWHITE && travel == 0)
				{
					movingPartNumber = PawnWHITE;
					Move = PawnWh;
					board[y][x] = 0;
				}
				if (board[y][x] == 0)
				{
					move = 1;
					oldPos.x = x;
					oldPos.y = y;
				}
			}
		}
	}
}

void Chess::mouseButtonReleasedOnPawn(Vector2i pos)
{
	if (e.type == Event::MouseButtonReleased)
	{
		if (e.key.code == Mouse::Left)
		{
			int ok = 2;

			if (movingPartNumber == PawnWHITE && move == 1)
			{
				ok = pawnMovement(oldPos.x, oldPos.y, x, y);
			}
			if (ok == 1)
			{
				board[y][x] = movingPartNumber;

				if (travel == 0) //Change of move, white to black
				{

					travel = 1;
				}

			}
			else if (ok == 0)
			{
				board[oldPos.y][oldPos.x] = movingPartNumber;
			}
			move = 0;
		}
	}
}

void Chess::movePawnAI()
{
	if (travel == 1)
	{
		//coordinates[0] {currentX}, coordinates[1] {currentY} 
		//coordinates[2] {newX}, coordinates[3] {newY}
		vector<int> coordinates(4);
		coordinates = aiChess.bestmove(board);

		if (pawnMovement(coordinates[0], coordinates[1], coordinates[2], coordinates[3]))
		{
			std::swap(board[coordinates[1]][coordinates[0]], board[coordinates[3]][coordinates[2]]);
		}
		travel = 0;
	}
}

void Chess::renderingSprites(Vector2i pos)
{
	window.clear();
	window.draw(Plank);

	if (move == 1)
	{
		Move.setPosition(pos.x - dx, pos.y - dy);
		window.draw(Move);
	}

	for (int i = 0; i < LENGHT; i++)
	{
		for (int j = 0; j < LENGHT; j++)
		{
			if (board[i][j] != 0)
			{
				if (board[i][j] == PawnBLACK)
				{
					PawnBl.setPosition(j * size, i * size);
					window.draw(PawnBl);
				}
				if (board[i][j] == PawnWHITE)
				{
					PawnWh.setPosition(j * size, i * size);
					window.draw(PawnWh);
				}
			}


		}
	}

	if (gameOver == 1)
	{
		window.draw(GameOverBlack);
	}
	if (gameOver == 2)
	{
		window.draw(GameOverWhite);
	}

}