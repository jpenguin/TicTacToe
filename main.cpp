// getch does not work properly in CLions debug console
// 4 space indent, QT style
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "conio.h"

using namespace std;

void drawBoard(string playerNames[2]);
void inputCoordinates(string playerNames[2]);
void randomAI(string playerNames[2]);
void clearBoard();
bool checkWin(string playerNames[2]);
void newGame(string playerNames[2]);
void clearScreen();

char grid[3][3], numPayers;

short turns;

bool won;

int main()
{
	string playerNames[2];
	int n = sizeof(playerNames) / sizeof(playerNames[0]);
	cout << "\nOne or two players? (1/2) ";
	do {
		numPayers = getche();
		cout << endl;
		switch (numPayers) {
			case '1': cout << "\nPlayer one, enter you name: ";
				getline(cin, playerNames[0]);
				playerNames[1] = "The Computer";
				break;
			case '2': cout << "\nPlayer one, enter you name: ";
				getline(cin, playerNames[0]);
				cout << "\nPlayer two, enter you name: ";
				getline(cin, playerNames[1]);
				cout << "Randomize who goes first? (y/n)";
				if (getch() == 'y' || getch() == 'Y')
					shuffle(playerNames, playerNames + n, mt19937(random_device()()));
				//else
				//	cout << "no";
				break;
			default: numPayers = 'E';
				//cout << "default";
				break;
		}
	}
	while (numPayers == 'E');
	cout << endl;
	newGame(playerNames);
	return 0;
}

void newGame(string playerNames[2])
{
	clrscr();
	won = false;
	turns = 0;
        clearBoard();
	drawBoard(playerNames);
}
void drawBoard(string playerNames[2])
{
    clearScreen();

	cout << "---+---+---+---|\n";
	cout << "2  |" << setw(3) << grid[2][0] << "|" << setw(3) << grid[2][1]
		 << "|" << setw(3) << grid[2][2] << "|\n";
	cout << "---+---+---+---|\n";
	cout << "1  |" << setw(3) << grid[1][0] << "|" << setw(3) << grid[1][1]
		 << "|" << setw(3) << grid[1][2] << "|\n";
	cout << "---+---+---+---|\n";
	cout << "0  |" << setw(3) << grid[0][0] << "|" << setw(3) << grid[0][1]
		 << "|" << setw(3) << grid[0][2] << "|\n";
	cout << "---+---+---+---|\n";
	cout << "   | 0 | 1 | 2 |\n";

	if (!won)
		inputCoordinates(playerNames); // player goes first
}

void clearBoard()
{
	// for (int a = 0; a < 3; a++) {
	for (auto &a: grid) {
		for (char &b: a) {
			b = ' ';
		}
	}
}

bool checkWin(string playerNames[2])
{
	char playAgain;
	// rows
	if ((grid[0][0] == grid[0][1]) && (grid[0][1] == grid[0][2])
		&& (grid[0][1]) != ' ')
		won = true;
	else if ((grid[1][0] == grid[1][1]) && (grid[1][1] == grid[1][2])
		&& (grid[1][1]) != ' ')
		won = true;
	else if ((grid[2][0] == grid[2][1]) && (grid[2][1] == grid[2][2])
		&& (grid[2][1]) != ' ')
		won = true;
		// columns
	else if ((grid[0][0] == grid[1][0]) && (grid[1][0] == grid[2][0])
		&& (grid[2][0]) != ' ')
		won = true;
	else if ((grid[0][1] == grid[1][1]) && (grid[1][1] == grid[2][1])
		&& (grid[2][1]) != ' ')
		won = true;
	else if ((grid[0][2] == grid[1][2]) && (grid[1][2] == grid[2][2])
		&& (grid[2][2]) != ' ')
		won = true;
		// diagonal
	else if ((grid[0][0] == grid[1][1]) && (grid[1][1] == grid[2][2])
		&& (grid[2][2]) != ' ')
		won = true;
	else if ((grid[2][0] == grid[1][1]) && (grid[1][1] == grid[0][2])
		&& (grid[0][2]) != ' ')
		won = true;
	else if (turns == 8) {
		won = true;
		drawBoard(playerNames);
		cout << "Draw\nPlay again (y/n):  ";
		cin.ignore();
                playAgain = getch();
		if (playAgain == 'y' || playAgain == 'Y')
			main();
		else {
			cout << endl;
			exit(0);
		}
	}
	else
		return false;

	if (won) {
		drawBoard(playerNames);

		cout << playerNames[turns % 2] << " has won\n\nPlay again (y/n):  ";
		cin.ignore();
                playAgain = getch();
		if (playAgain == 'y' || playAgain == 'Y')
			main();
		else {
			cout << endl;
			exit(0);
		}
	}
}

void inputCoordinates(string playerNames[2])
{
	int x, y;
	do {
		cout << playerNames[turns % 2] << ", what square would you like (x y):  ";
		cin >> y >> x;
	}
	while (grid[x][y] != ' ');
	if (turns % 2)
		grid[x][y] = 'O';
	else
		grid[x][y] = 'X';

	checkWin(playerNames);
	turns++;
	if (numPayers == '1')
            randomAI(playerNames); // random randomAI
	else
		drawBoard(playerNames);
}

void randomAI(string playerNames[2])
{
	unsigned x, y;

	//if (grid[0][0] == ' ')
	//	grid[0][0] = 'O';
	//else {
	do {
		random_device dev;
		mt19937 rng(dev());
		uniform_int_distribution<mt19937::result_type> mark(0, 2);
		x = mark(rng);
		y = mark(rng);
	}
	while (grid[x][y] != ' ');
	grid[x][y] = 'O';
	//}

	(checkWin(playerNames));
	turns++;
	drawBoard(playerNames); // Draw board before players next turn
}

void clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}