#include <iostream>
#include "AIChess.h"
#include <vector>
using namespace std;

vector<int> AIChess::bestmove(int board[8][8])
{
	vector<int> result(4);

	int priority = 1;
	int comparisonPriority = 0;


	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[j][i] == 0)
				continue;
			comparisonPriority = 0;
			//Conditions for making a move
			if (board[j][i] == player && (pawnMovement(i, j, i, j - 1, board) || pawnMovement(i, j, i, j + 1, board) || pawnMovement(i, j, i - 1, j, board) || pawnMovement(i, j, i + 1, j, board)))
			{
				//House
				if (i < 3 && j < 3 && (pawnMovement(i, j, i + 1, j, board) || pawnMovement(i, j, i, j + 1, board)))
				{
					comparisonPriority = overwriteIfMore(comparisonPriority, 100);
				}
				//Center on the top

				else if (j > 2 && j < 5 && i < 3 && (pawnMovement(i, j, i + 1, j, board) || pawnMovement(i, j, i, j + 1, board)))
				{
					comparisonPriority = overwriteIfMore(comparisonPriority, 95);
				}
				//left mid
				else if (j < 3 && i > 2 && i < 5 && (pawnMovement(i, j, i + 1, j, board) || pawnMovement(i, j, i, j + 1, board)))
				{
					comparisonPriority = overwriteIfMore(comparisonPriority, 90);
				}
				//enemy corner
				else if (j > 4 && i > 4 && (pawnMovement(i, j, i + 1, j, board) || pawnMovement(i, j, i, j + 1, board)))
				{
					comparisonPriority = overwriteIfMore(comparisonPriority, 89);

				}
				//mid
				else if (j > 2 && j < 5 && i > 2 && i < 5 && (pawnMovement(i, j, i + 1, j, board) || pawnMovement(i, j, i, j + 1, board)))
				{
					comparisonPriority = overwriteIfMore(comparisonPriority, 85);
				}
				//Bottom left
				else if (j > 4 && i < 5 && (pawnMovement(i, j, i + 1, j, board) || pawnMovement(i, j, i, j + 1, board) || pawnMovement(i, j, i, j - 1, board)))
				{
					if (CheckingEmploymentHorizontal(j, board) == 3 && (pawnMovement(i, j, i, j - 1, board) || pawnMovement(i, j, i + 1, j, board)))
					{
						comparisonPriority = overwriteIfMore(comparisonPriority, 79);
					}
					else if ((pawnMovement(i, j, i + 1, j, board) || pawnMovement(i, j, i, j + 1, board)) || (pawnMovement(i, j, i, j - 1, board) && board[j - 1][i + 1] == enemy))
					{
						comparisonPriority = overwriteIfMore(comparisonPriority, 80);
					}
					if (((!(pawnMovement(i, j, i + 1, j, board)) || (!pawnMovement(i, j, i, j + 1, board)) || (!pawnMovement(i, j, i, j - 1, board))) == 0) && pawnMovement(i, j, i - 1, j, board))
					{
						comparisonPriority = overwriteIfMore(comparisonPriority, 50);
					}

				}
				//Right up
				else if (j < 5 && i > 4 && (pawnMovement(i, j, i + 1, j, board) || pawnMovement(i, j, i, j + 1, board) || pawnMovement(i, j, i - 1, j, board)))
				{
					if (CheckingEmploymentVertical(i, board) && pawnMovement(i, j, i - 1, j, board))
					{
						comparisonPriority = overwriteIfMore(comparisonPriority, 74);
					}
					else if (pawnMovement(i, j, i, j + 1, board) || pawnMovement(i, j, i + 1, j, board) || pawnMovement(i, j, i - 1, j, board))
					{
						comparisonPriority = overwriteIfMore(comparisonPriority, 75);
					}
					if ((!(pawnMovement(i, j, i + 1, j, board)) || (!pawnMovement(i, j, i, j + 1, board)) || (!pawnMovement(i, j, i - 1, j, board))) == 0)
					{
						comparisonPriority = overwriteIfMore(comparisonPriority, 49);
					}
				}

				if (priority <= comparisonPriority)
				{
					priority = comparisonPriority;
					result[0] = i;
					result[1] = j;
					switch (priority)
					{
					case 100:
						if (pawnMovement(i, j, i + 1, j, board))
						{
							result[2] = i + 1;
							result[3] = j;
						}
						else if (pawnMovement(i, j, i, j + 1, board))
						{
							result[2] = i;
							result[3] = j + 1;
						}

						break;
					case 95:
						if (pawnMovement(i, j, i + 1, j, board))
						{
							result[2] = i + 1;
							result[3] = j;
						}
						else if (pawnMovement(i, j, i, j + 1, board))
						{
							result[2] = i;
							result[3] = j + 1;
						}
						break;
					case 90:
						if (pawnMovement(i, j, i, j + 1, board))
						{
							result[2] = i;
							result[3] = j + 1;
						}
						else if (pawnMovement(i, j, i + 1, j, board))
						{
							result[2] = i + 1;
							result[3] = j;
						}
						break;
					case 89:
						if (pawnMovement(i, j, i, j + 1, board))
						{
							result[2] = i;
							result[3] = j + 1;
						}
						else if (pawnMovement(i, j, i + 1, j, board))
						{
							result[2] = i + 1;
							result[3] = j;
						}
						break;
					case 85:

						if (pawnMovement(i, j, i, j + 1, board))
						{
							result[2] = i;
							result[3] = j + 1;
						}
						else if (pawnMovement(i, j, i + 1, j, board))
						{
							result[2] = i + 1;
							result[3] = j;
						}
						break;
					case 80:
						if (pawnMovement(i, j, i + 1, j, board))
						{
							result[2] = i + 1;
							result[3] = j;
						}
						else if (pawnMovement(i, j, i, j + 1, board))
						{
							result[2] = i;
							result[3] = j + 1;
						}
						else if (pawnMovement(i, j, i, j - 1, board))
						{
							result[2] = i;
							result[3] = j - 1;
						}
						break;
					case 79:
						if (pawnMovement(i, j, i, j - 1, board))
						{
							result[2] = i;
							result[3] = j - 1;
						}
						else if (pawnMovement(i, j, i + 1, j, board))
						{
							result[2] = i + 1;
							result[3] = j;
						}
						break;
					case 75:
						if (pawnMovement(i, j, i, j + 1, board))
						{
							result[2] = i;
							result[3] = j + 1;
						}
						else if (pawnMovement(i, j, i + 1, j, board))
						{
							result[2] = i + 1;
							result[3] = j;
						}
						else if (pawnMovement(i, j, i - 1, j, board))
						{
							result[2] = i - 1;
							result[3] = j;
						}
						break;
					case 74:
						if (pawnMovement(i, j, i - 1, j, board))
						{
							result[2] = i - 1;
							result[3] = j;
						}
						break;
					case 50:
						if (pawnMovement(i, j, i - 1, j, board))
						{
							result[2] = i - 1;
							result[3] = j;
						}
						break;
					case 49:
						if (pawnMovement(i, j, i, j - 1, board))
						{
							result[2] = i;
							result[3] = j - 1;
						}
						break;
					default:
						break;
					}
				}
			}
		}
	}
	return result;
}


int AIChess::overwriteIfMore(int number, int x)
{
	if (number < x)
	{
		return x;
	}
	return number;
}

int AIChess::CheckingEmploymentHorizontal(int j, int board[8][8])
{
	int result = 0;
	for (int i = j; i > 4; i--)
	{
		if (board[j][i] != 0)
		{
			result++;
		}
	}
	return result;
}

int AIChess::CheckingEmploymentVertical(int i, int board[8][8])
{
	int result = 0;
	for (int j = i; i > 4; i--)
	{
		//if (board[i][j] == 1)
		//{
		//	result;
		//}
	}
	if (8 - result == result)
	{
		return true;
	}
	return 0;
}

int AIChess::pawnMovement(int currentX, int currentY, int newX, int newY, int board[8][8])
{
	//up
	if (newY == currentY - 1 && newX == currentX && board[currentY - 1][currentX] == 0 && currentY != 0)
	{
		return 1;
	}
	//down
	if (newY == currentY + 1 && newX == currentX && board[currentY + 1][currentX] == 0 && currentY != 7)
	{
		return 1;
	}
	//left
	if (newY == currentY && newX == currentX - 1 && board[currentY][currentX - 1] == 0 && currentX != 0)
	{
		return 1;
	}
	//right
	if (newY == currentY && newX == currentX + 1 && board[currentY][currentX + 1] == 0 && currentX != 7)
	{
		return 1;
	}
	return 0;
}