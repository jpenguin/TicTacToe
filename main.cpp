// 4 space indent, QT style
#include "getch.h"
#include <iomanip>
#include <iostream>
#include <stdio.h>

void drawBoard();

void inputCordnates();

void AI();

void newBoard();

bool checkWin();

char grid[3][3];

bool won;

using namespace std;

int main()
{
	won = false;
	newBoard();
	drawBoard();
	return 0;
}

void drawBoard()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif

	cout << "---+---+---+---|\n";
	cout << "2  |" << setw(3) << grid[2][0] << "|" << setw(3) << grid[2][1] << "|"
		 << setw(3) << grid[2][2] << "|\n";
	cout << "---+---+---+---|\n";
	cout << "1  |" << setw(3) << grid[1][0] << "|" << setw(3) << grid[1][1] << "|"
		 << setw(3) << grid[1][2] << "|\n";
	cout << "---+---+---+---|\n";
	cout << "0  |" << setw(3) << grid[0][0] << "|" << setw(3) << grid[0][1] << "|"
		 << setw(3) << grid[0][2] << "|\n";
	cout << "---+---+---+---|\n";
	cout << "   | 0 | 1 | 2 |\n";

	if (!won)
		inputCordnates(); // player goes first
}

void newBoard()
{
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			grid[a][b] = ' ';
		}
	}
}

bool checkWin()
{
	// rows
	if ((grid[0][0] == grid[0][1]) && (grid[0][1] == grid[0][2]) &&
		(grid[0][1]) != ' ')
		return true;
	else if ((grid[1][0] == grid[1][1]) && (grid[1][1] == grid[1][2]) &&
		(grid[1][1]) != ' ')
		return true;
	else if ((grid[2][0] == grid[2][1]) && (grid[2][1] == grid[2][2]) &&
		(grid[2][1]) != ' ')
		return true;
		// collumns
	else if ((grid[0][0] == grid[1][0]) && (grid[1][0] == grid[2][0]) &&
		(grid[2][0]) != ' ')
		return true;
	else if ((grid[0][1] == grid[1][1]) && (grid[1][1] == grid[2][1]) &&
		(grid[2][1]) != ' ')
		return true;
	else if ((grid[0][2] == grid[1][2]) && (grid[1][2] == grid[2][2]) &&
		(grid[2][2]) != ' ')
		return true;
		// diagnal
	else if ((grid[0][0] == grid[1][1]) && (grid[1][1] == grid[2][2]) &&
		(grid[2][2]) != ' ')
		return true;
	else if ((grid[2][0] == grid[1][1]) && (grid[1][1] == grid[0][2]) &&
		(grid[0][2]) != ' ')
		return true;
	else
		return false;
}

void inputCordnates()
{
	int x, y;
	char t = 'X';
	do {
		cout << "What square would you like (x y):  ";
		cin >> y >> x;
	}
	while (grid[x][y] != ' ');
	grid[x][y] = t;

	if (checkWin()) {
		won = true;
		drawBoard();
		cout << "Congratulations, you won\n\nNew Game (y/n)?\n";
		cin.ignore();
		t = getch();
		if (t == 'y' || t == 'Y')
			main();
		else
			exit(0);
	}
	AI(); // random AI
}

void AI()
{
	int x, y;
	char t = 'O';

	if (grid[0][0] == ' ')
		grid[0][0] = t;
	else {
		do {
			x = rand() % 3;
			y = rand() % 3;
		}
		while (grid[x][y] != ' ');
		grid[x][y] = t;
	}

	if (checkWin()) {
		won = true;
		drawBoard();
		cout << "Congratulations, you lost\n\nNew Game (y/n)?\n";
		cin.ignore();
		t = getch();
		if (t == 'y' || t == 'Y')
			main();
		else
			exit(0);
	}
	drawBoard(); // Draw board before players next turn
}
