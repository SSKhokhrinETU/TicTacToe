#include "pch.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

using namespace std;

short int input()
{
	short int number = 0;
	while ((number > 5) || (number < 3))
	{
		cout << "Input:\n";
		number = _getch();
		_getch();
		if ((number > 47) && (number < 58))
		{
			number -= 48;
			cout << number;
		}
		else
			number = 0;
		system("cls");
		cout << "Incorrect input, new:\n";
	}
	return number;
}

void gameField(char (&matrix)[5][5], short int X, short int Y, short int sizeX, short int sizeY)
{
	cout << "\xC9\xCD\xCD\xCD";
	for (int i = 1; i < sizeX; i++)
		cout << "\xCB\xCD\xCD\xCD";
	cout << "\xBB\n\xBA ";
	for (int i = 0; i < sizeX; i++)
		cout << " " << " \xBA ";
	cout << "\n\xBA ";
	for (int i = 0; i < sizeX; i++)
		cout << matrix[0][i] << " \xBA ";
	cout << '\n';
	for (int i = 1; i < sizeY; i++)
	{
		cout << "\xCC\xCD\xCD\xCD";
		for (int j = 1; j < sizeX; j++)
			cout << "\xCE\xCD\xCD\xCD";
		cout << "\xB9\n\xBA ";
		for (int j = 0; j < sizeX; j++)
			cout << " " << " \xBA ";
		cout << "\n\xBA ";
		for (int j = 0; j < sizeX; j++)
			cout << matrix[i][j] << " \xBA ";
		cout << '\n';
	}
	cout << "\xC8\xCD\xCD\xCD";
	for (int i = 1; i < sizeX; i++)
		cout << "\xCA\xCD\xCD\xCD";
	cout << "\xBC";
}

bool isWin(char(&matrix)[5][5], short int sizeX, short int sizeY)
{
	bool win = false;
	for (int i = 0; i < sizeY; i++)
		for (int j = 0; j < sizeX; j++)
		{
			if (((i - 1) >= 0) && ((i + 1) < sizeY))
				if ((matrix[i][j] == matrix[i - 1][j]) && (matrix[i][j] == matrix[i + 1][j]) && matrix[i][j])
					win = true;
			if (((j - 1) >= 0) && ((j + 1) < sizeX))
				if ((matrix[i][j] == matrix[i][j - 1]) && (matrix[i][j] == matrix[i][j + 1]) && matrix[i][j])
					win = true;
			if (((i - 1) >= 0) && ((i + 1) < sizeY) && ((j - 1) >= 0) && ((j + 1) < sizeX)) {
				if ((matrix[i][j] == matrix[i - 1][j - 1]) && (matrix[i][j] == matrix[i + 1][j + 1]) && matrix[i][j])
					win = true;
				if ((matrix[i][j] == matrix[i - 1][j + 1]) && (matrix[i][j] == matrix[i + 1][j - 1]) && matrix[i][j])
					win = true;
			}
		}
	return win;
}

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

int main()
{
	char field[5][5] = { 0 };
	short int ptrX = 0, ptrY = 0, width = 0, height = 0;
	bool isEnd = false, done = false, doneX = false;
	short int oX = 0, oY = 0;
	char choose = 0, tempChoose = 0;
	short int counter = 0;
	
	srand(time(0));
	system("color F8");
	system("color 0F");
	system("color 4B");

	/*hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 8));*/

	cout << "Width of field\n";
	width = input();
	system("cls");
	cout << "Height of field\n";
	height = input();

	while (!isEnd && (counter <= (width * height)))
	{
		system("cls");
		gameField(field, ptrX, ptrY, width, height);
		gotoxy((2 + 4 * ptrX), (1 + 3 * ptrY));
		printf("%1c", 194);
		gotoxy(0, 20);
		while ((choose != 13) && (doneX == false))
		{
			do
			{
				choose = _getch();
				if (choose == -32)
					tempChoose = _getch();
			} while ((choose != -32) && (choose != 13));
			doneX = false;
			if (choose == 13)
			{
				if (field[ptrY][ptrX] == 0)
				{
					field[ptrY][ptrX] = 'X';
					doneX = true;
				}
			}
			else {
				gotoxy((2 + 4 * ptrX), (1 + 3 * ptrY));
				printf("%1c", 32);
				gotoxy(0, 20);
				switch (tempChoose)
				{
				case 72:			//up
					if (ptrY > 0)
						ptrY--;
					break;
				case 80:			//down
					if (ptrY < (height - 1))
						ptrY++;
					break;
				case 75:			//left
					if (ptrX > 0)
						ptrX--;
					break;
				case 77:			//right
					if (ptrX < (width - 1))
						ptrX++;
					break;
				}
			}
			gotoxy((2 + 4 * ptrX), (1 + 3 * ptrY));
			printf("%1c", 194);
			gotoxy(0, 20);
			choose = 0;
		}
		choose = 0;
		done = true;
		isEnd = isWin(field, width, height);
		counter++;
		if (isEnd)
			break;
		done = false;
		while (!done) {
			oX = rand() % width;
			oY = rand() % height;
			if (field[oY][oX] == 0)
			{
				field[oY][oX] = 'O';
				done = true;
			}
		}
		
		isEnd = isWin(field, width, height);
		done = false;
		doneX = false;
		counter++;
	}
	system("cls");

	gameField(field, ptrX, ptrY, width, height);
	if (counter >= 25)
		cout << "No winner";
	else
		cout << "\n\n\n" << (done ? "\"X\" wins" : "\"O\" wins");

	return 0;
}
