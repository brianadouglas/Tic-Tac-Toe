#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

//Player is X
//Computer is O

typedef struct move{
	int x, y;
}move;


//Initialises each space to NULL in the board
void initialise_board(char b[3][3])
{
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			b[x][y] = '-';
		}
	}
}

//Displays the tic-tac-toe game
void showBoard (char curr_board[3][3])
{
	printf("\t  0 || 1 || 2\n");
	for (int x = 0; x < 3; x++)
	{
		printf("\t%d %c || %c || %c\n", x, curr_board[x][0],curr_board[x][1],curr_board[x][2]);
	}
}

//Returns the maximum of 2 numbers
int max(int num1, int num2)
{
	return (num1 > num2) ? num1 : num2;
}

//Returns the minimum of 2 numbers
int min(int num1, int num2)
{
	return (num1 < num2) ? num1 : num2;
}

//Check if a move can be made based on whether or not the space is 
//empty
bool isEmpty(move m, char b[3][3])
{
	if (b[m.x][m.y] == '-')
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Creates an array of available moves
void findFree(char b[3][3], move freeSpaces[])
{
	move m;
	int index = 0;
	for (int i=0; i<3; i++)
	{
		for(int i2=0; i2<3; i2++)
		{
			if (b[i][i2] == '-')
			{
				m.x = i;
				m.y = i2;
				freeSpaces[index] = m;
				index++;
			}
		}
	}
}

//Place recently-made move on the board.
void makeMove(char mark, move m, char b[3][3])
{
	b[m.x][m.y] = mark;
}


//Evaluates the value of the board and used to determine if there has been
//a winner
int gameWon(char b[3][3])
{
	for (int i=0; i<3; i++)
	{
		if(b[i][0] == b[i][1] && b[i][1] == b[i][2] && b[i][0] != '-')
		{
			if (b[i][0] == 'X')
			{
				return -10;
			}
			else 
			{
				return 10;
			}
		}

		else if(b[0][i] == b[1][i]  && b[1][i] == b[2][i] && b[0][i] != '-')
		{
			if (b[i][0] == 'X')
			{
				return -10;
			}
			else
			{
				return 10;
			}
		}

	}
	if (b[0][0] == b[1][1] && b[1][1] == b[2][2] && b[0][0] != '-')
	{
		if (b[0][0] == 'X')
		{
			return -10;
		}
		else 
		{
			return 10;
		}
	}

	if (b[2][0] == b[1][1] && b[1][1] == b[0][2] && b[2][0] != '-')
	{
		if(b[2][0] == 'X')
		{
			return -10;
		}
		else 
		{
			return 10;
		}
	}
	return 0;
}

//Minimax algorithm
int minimax(char temp[3][3],bool is_max)
{
	int score = gameWon(temp);
	if (score!= 0)
	{
		return score;
	}
	int best;
	if (is_max)
	{
		best = -1000;
		for (int i=0; i<3; i++)
		{
			for (int i2=0; i2<3; i2++)
			{
				if (temp[i][i2] == '-')
				{
					temp[i][i2] = 'O';
					best = max(best, minimax(temp,!is_max));
					temp[i][i2] = '-';
				}
			}
		}
	}
	else
	{
		best = 1000;
		for (int i=0; i<3; i++)
		{
			for (int i2=0; i2<3; i2++)
			{
				if (temp[i][i2] == '-')
				{
					temp[i][i2] = 'X';
					best = min(best, minimax(temp,!is_max));
					temp[i][i2] = '-';
				}
			}
		}
	}
	return best;
}
//Makes the best move for the computer
move bestMove(char board[3][3])
{
    int best = -1000;
    move optimal;
 
    for (int i = 0; i<3; i++)
    {
        for (int i2 = 0; i2<3; i2++)
        {
            if (board[i][i2]=='-')
            {
                board[i][i2] = 'O';
                int score = minimax(board,true);
                board[i][i2] = '-';
                if (score > best)
                {
                    optimal.x = i;
                    optimal.y = i2;
                    best = score;
                }
            }
        }
    }
    return optimal;
}

//Player or computer(AI) chooses move
void chooseMove(char player, char b[3][3], int spaces_left)
{
	bool empty = false;
	move current_move;
	char mark;
	printf("%c\n", player);
	if (player == 'X')
	{
		while(!empty)
		{
			scanf("%d %d", &current_move.x, &current_move.y);
			printf("\n");
			empty = isEmpty(current_move, b);
		}
		makeMove(player, current_move, b);
	}
	else
	{
		current_move = bestMove(b);
		makeMove(player, current_move, b);
	}
}



int main(){
	char board[3][3];
	int spaces = 9;
	char player;
	int won = 0;;
	initialise_board(board);

	printf("TIC TAC TOE\n");
	printf("Player goes first\n");

	while (spaces > 0)
	{
		showBoard(board);
		player = 'X';
		chooseMove(player, board, spaces);
		spaces--;
		won = gameWon(board);
		if (won != 0)
		{
			break;
		}
		showBoard(board);
		player = 'O';
		chooseMove(player, board, spaces);
		spaces--;
		won = gameWon(board);
		if (won != 0)
		{
			break;
		}
		
	}
	showBoard(board);
	if (won == 0)
	{
		printf("The game resulted in a tie\n");
	}
	else if (won == -10)
	{
		printf("The player has won the game\n");
	}
	else
	{
		printf("The computer has won the game\n");
	}

	return 0;
}