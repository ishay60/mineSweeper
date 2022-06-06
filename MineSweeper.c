#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h> //enables usage of "srand" function
#include <time.h>



#define COLS 8
#define ROWS 8 
#define NUMBOMBS 8 
#define BOMB '*'
#define HIDDEN 'X'
#define BLANK ' '


int menuChoice(); 
void cheats(int table[][COLS], char fronttable[][COLS], int x);

void printTable(char table[][COLS]);
void intializeFront(char table[][COLS]);
void plantBombs(int table[][COLS]);
void initBackground(int table[][COLS]); 
bool isInRange(int n, int max, int min);
char convertToChar(int value);
void nearBomb(int bRow, int bCol, int table[][COLS]);
void result(bool isWin, char front[][COLS], int back[][COLS]);

void main()
{/*this is the main function of classic MINESWEEPER , most of the user interface , oucurrs in the main function (user interface , win conditions lose condition etc.
 most of the check ups , and special features , like cheat , are embeded along the main with function calling .*/
	int userGameChoice = 1;
	char frontTable[ROWS][COLS];
	int backgroundTable[ROWS][COLS];
	/*int n, max, min;*/
	int value;
	int row, col;
	bool endOfGame = false;
	bool bombExplodes = false;
	int counter = 0;





	userGameChoice = menuChoice();


	while (userGameChoice != 0 && userGameChoice != 1)
	{//  At this point , menu choice is limited to the first option only .
		printf("Please enter the number 1.\n");
		scanf("%d", &userGameChoice);
	}
	intializeFront(frontTable);
	initBackground(backgroundTable);
	printTable(frontTable);
	plantBombs(backgroundTable);

	while (!endOfGame)
	{/*user interface , prompts the user with instruction , and input request.*/
		printf("Please enter your move, row and column");
		scanf("%i%i", &row, &col);
		if (row == -1 && col > 0)//the "cheat" condition check.
		{
			cheats(backgroundTable, frontTable, col);
			counter = counter + col;
			if (counter >= ROWS * COLS - NUMBOMBS)
				endOfGame = true;//checks if user has uncovered whole of the brackets that has no bombs in it .
		}
		else
		{
			while (!isInRange(row, 0, 7) || !isInRange(col, 0, 7))//checks if the user input is valid throughout the game.
			{
				printf("please enter a valid choice\n");
				scanf("%d%d", &row, &col);
			}
			if (frontTable[row][col] == HIDDEN)/*checks if the user prompts an unopen or open bracket.*/
			{
				frontTable[row][col] = convertToChar(backgroundTable[row][col]);// opens up the selected bracket . cleans up the rest of what showed before .
				counter++;
				system("cls");




				if (backgroundTable[row][col] == -1)//game lose condition.
				{
					endOfGame = true;
					bombExplodes = true;
				}
				else if (counter == ROWS * COLS - NUMBOMBS) // game win condition.
				{
					endOfGame = true;
				}
			}
			else

				printf("you have already entered that input , please enter a diffrent input. \n");//what prompts if the user

		}
		
		printTable(frontTable);//keeps up the table in front of the user .
	}

		if (bombExplodes)
		{
			printf("you have hit a bomb , GAME OVER !\n"); // lose message 
			DiscoverTheField(frontTable, backgroundTable);
		}
		else if (!bombExplodes)
			printf("YOU HAVE WON THE GAME , WELL DONE !\n"); // win massage

	}

int menuChoice()
{//software opens up with menu , this function prints the menu , and prompts the user to choose , at this moment only for choice number 1 .
	int userChoice;
	printf("Welcome to Minesweeper!\n");
	printf("Please choose one of the following options and enter it's number\n");

	printf("1 - for size 8X8\n");
	printf("2 - for size 12X12    \n");
	printf("3 - for size 15X15	  \n");
	printf("4 - for custom size	  \n");
	printf("0 - Exit			  \n");
	scanf("%d", &userChoice);
	return userChoice;
	
	
} 
void cheats(int table[][COLS], char fronttable[][COLS], int x)
{/* this cheat supposed to open up as many brackets entered after typing in "-1" for the rows 
	, and whatever numbers of brackets the player wants to open ,
	(does not work on bombs and on more then the availabe hidden brackets.*/
	int row, col;

	for (row = 0; row < ROWS; row++)
	{
		for (col = 0; col < COLS; col++)
		{
			if (table[row][col] != -1 && fronttable[row][col] == HIDDEN)
			{
				fronttable[row][col] = convertToChar(table[row][col]);
				x--;
				if (x == 0)
				{
					return;
				}
			}
		}
	}

}
void intializeFront(char table[][COLS])
{/* makes an array for the hidden bombs and number , starts all with X's*/
	int i, j;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{ 
			table[i][j] = HIDDEN;
		}
	}
}
void initBackground(int table[][COLS])
{/* initializes an array of int , sets all to zero.*/
	int i, j;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
			table[i][j] = 0;
	}

}

void plantBombs(int table[][COLS])
{/*  a random function , plants bombs on the int array , with the mark -1 */
	srand(time(NULL));
	int i, j;
	int bombCount = 0;
	while (bombCount < 8)
	{
		i = rand() % 8;
		j = rand() % 8;
		if (table[i][j] != -1)
		{
			table[i][j] = -1;
			nearBomb(i, j, table);
			bombCount++;
		}
	}
}


void nearBomb(int bRow, int bCol, int table[][COLS])
{
	int row, col;

	//runs from i -1 to i + 1(i index of rows) to search the bomb
	for (row = bRow - 1; row <= bRow + 1; row++)
	{
		// runs from i-1 to i +1 (i index of cols) to search the bomb
		for (col = bCol - 1; col <= bCol + 1; col++)
		{
			if (isInRange(row, 0, 7) && isInRange(col, 0, 7))
			{
				if (table[row][col] != -1)
					table[row][col]++;
			}
		}


	}
}

bool isInRange(int n, int min, int max)
{/*range check , will be used in another function to return true or false*/
	return((n >= min) && (n <= max));
}
void printTable(char table[][COLS])
{/*game table print */
	int i, j;
	printf("        0   1   2   3   4   5   6   7\n");
	printf("   ___________________________________\n\n");
	for (i = 0; i < ROWS; i++)
	{
		printf("  | %d " ,i);
		for (j = 0; j < COLS; j++)
		{
			printf("| %c ", table[i][j]);
		}
		printf("|\n");
	}
	printf("   ___________________________________\n");
}





void DiscoverTheField(char front[][COLS], int back[][COLS])
{
	int i, j;
	int value;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			front[i][j] = convertToChar( back[i][j]);
		}
			
		
	}
}

char convertToChar(int value)
{/*takes the int value from back array and puts corresponding value in chars .*/
	if (value == -1)
	{
		return BOMB;
	}
	else if (value == 0)
	{
		return BLANK;
	}
	else if (isInRange(value, 1, 8))
	{
		return value + '0';

	}
}
