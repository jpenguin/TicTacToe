// 4 space indent, QT style
#include <iomanip>
#include <iostream>
#include <string>
#include "extern/cpackets/conio.h"

void newGame();
void drawBoard(std::string playerNames[2]);
void inputCoordinates(std::string playerNames[2]);
void AI(std::string playerNames[2]);
void newBoard();
bool checkWin(std::string playerNames[2]);
void newGame(std::string playerNames[2]);
using namespace std;

char grid[3][3];

string playerNames[2];

short turns;

bool won;

int main()
{
	char ans;
	cout << "One or two players? (1/2)";
	do {
		ans = getch();
		cout << endl;
		switch (ans) {
			case '1': cout << "\nPlayer one, enter you name: ";
				getline(cin, playerNames[0]);
				playerNames[1] = "The Computer";
				break;
			case '2':  //two player is NYI
				cout << "\nPlayer one, enter you name: ";
				getline(cin, playerNames[0]);
				cout << "\nPlayer two, enter you name: ";
				getline(cin, playerNames[1]);
				break;
			default: ans = 'E';
				cout << "default";
				break;
		}
		cout << ans;
		newGame(playerNames);
	}
	while (ans == 'E');
	return 0;
}

void newGame(string playerNames[2])
{
	won = false;
	newBoard();
	drawBoard(playerNames);
}
void drawBoard(string playerNames[2])
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif

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

void newBoard()
{
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			grid[a][b] = ' ';
		}
	}
}

bool checkWin(string playerNames[2])
{
	char ans;
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
	else
		return false;

	if (won) {
		drawBoard(playerNames);
		cout << playerNames[turns % 2] << " has won\n\nPlay again (y/n(:  ";
		cin.ignore();
		ans = getch();
		if (ans == 'y' || ans == 'Y')
			main();
		else
			exit(0);
	}
}

void inputCoordinates(string playerNames[2])
{
	int x, y;
	char t = 'X';
	do {
		cout << playerNames[turns % 2] << ", what square would you like (x y):  ";
		cin >> y >> x;
	}
	while (grid[x][y] != ' ');
	grid[x][y] = t;

	checkWin(playerNames);
	turns++;
	AI(playerNames); // random AI
}

void AI(string playerNames[2])
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

	(checkWin(playerNames));
	turns++;
	drawBoard(playerNames); // Draw board before players next turn
}
