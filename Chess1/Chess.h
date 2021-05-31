#include <SFML/Graphics.hpp>
#include <iostream>
#include "AIChess.h"
#include <vector>

using namespace sf;

struct position
{
	int x, y;
};

class Chess
{
private:
#define LENGHT 8
#define PawnBLACK 1
#define PawnWHITE -1

	position oldPos;
	int size = 100, move = 0, x, y;

	int board[8][8] =
	{ 1, 1, 1, 0, 0, 0, 0, 0,
	  1, 1, 1, 0, 0, 0, 0, 0,
	  1, 1, 1, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, -1, -1, -1,
	  0, 0, 0, 0, 0, -1, -1, -1,
	  0, 0, 0, 0, 0, -1, -1, -1, };

	// 0 White moves, 1 Black moves
	int travel = 0;

	//-----TEST

	RenderWindow window;
	Texture t1, t2, t3, t4, t5;

	Sprite Plank;//Board
	Sprite PawnBl;//pawn black
	Sprite PawnWh;//pawn white
	Sprite GameOverBlack;
	Sprite GameOverWhite;
	Sprite Move;

	AIChess aiChess;

	// gameOver == 1 White won, gameOver == 1 Black won, 0 game progress
	int gameOver = 0;

	// height = (window height  / size board)
	// width = (window width  / size board)
	int height = size, width = size;

	float dx = 0, dy = 0;

	//moving part number
	int movingPartNumber = 0;

	Event e;

public:
	Chess();
	void StartGame();
private:
	int pawnMovement(int currentX, int currentY, int newX, int newY);

	int checkWinnerWhite();

	int checkWinnerBlack();

	void defoltBoard();

	void checkingEndGame();

	void renderingSprites(Vector2i poz);
};




