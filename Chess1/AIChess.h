#include <iostream>
#include <vector>
using namespace std;

class AIChess
{
private:
	//Количество сделанных ходов | Number of moves made
	int player = 1, enemy = -1;

public:
	std::vector<int> bestmove(int board[8][8]);
private:
	//Returns the number of occupied cells in the enemy base in line i
	int CheckingEmploymentVertical(int i, int board[8][8]);
	//Returns the number of occupied cells in the enemy base in line j
	int CheckingEmploymentHorizontal(int j, int board[8][8]);
	//if x is greater than number it will return, otherwise number
	int overwriteIfMore(int number, int x);

	int pawnMovement(int currentX, int currentY, int newX, int newY, int board[8][8]);
};
