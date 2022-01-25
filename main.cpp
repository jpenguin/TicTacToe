// getch does not work properly in CLions debug console
// 4 space indent, QT style
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "cpackets/conio.h"

using namespace std;

void newGame(string playerNames[2]);
void nextTurn(string playerNames[2]);
void drawBoard();
void inputCoordinates(string playerNames[2]);
void randomAI();
void clearBoard();
bool gameOver();
void clearScreen();

char grid[3][3];

short turns;

int main()
{
    string playerNames[2];
    char numPlayers;
    int n = sizeof(playerNames) / sizeof(playerNames[0]);
    cout << "\nOne or two players? (1/2) ";
    do {
        numPlayers = getche();
        cout << endl;
        switch (numPlayers) {
        case '1':
            cout << "\nPlayer one, enter you name: ";
            getline(cin, playerNames[0]);
            playerNames[1] = "The Computer";
            break;
        case '2':
            cout << "\nPlayer one, enter you name: ";
            getline(cin, playerNames[0]);
            cout << "\nPlayer two, enter you name: ";
            getline(cin, playerNames[1]);
            // else
            //	cout << "no";
            break;
        default:
            numPlayers = '0';
            // cout << "default";
            break;
        }
    } while (numPlayers == '0');
    cout << "Randomize who goes first? (y/n)";
    if (getch() == 'y' || getch() == 'Y')
        shuffle(playerNames, playerNames + n, mt19937(random_device()()));

    cout << endl;
    newGame(playerNames);
    return 0;
}

void newGame(string playerNames[2])
{
    clearScreen();
    turns = 0;
    clearBoard();
    nextTurn(playerNames);
}
void nextTurn(string playerNames[2])
{
    drawBoard();

    if (playerNames[turns % 2].compare("The Computer") == 0)
        randomAI();
    else
        inputCoordinates(playerNames); // player goes first

    if (gameOver()) {
        drawBoard();
        if (turns == 8) {
            nextTurn(playerNames);
            cout << "Draw\nPlay again (y/n):  ";
            cin.ignore();
            if (getch() == 'y' || getch() == 'Y')
                main();
            else {
                cout << endl;
                exit(0);
            }
        } else {
            cout << playerNames[turns % 2] << " has won\n\nPlay again (y/n):  ";
            cin.ignore(100, '\n');
            if (getch() == 'y' || getch() == 'Y')
                main();
            else {
                cout << endl;
                exit(0);
            }
        }
    }
    turns++;
    nextTurn(playerNames);
}

void drawBoard()
{
    clearScreen();

    cout << "---+---+---+---|\n";
    cout << "2  |" << setw(3) << grid[2][0] << "|" << setw(3) << grid[2][1] << "|" << setw(3)
         << grid[2][2] << "|\n";
    cout << "---+---+---+---|\n";
    cout << "1  |" << setw(3) << grid[1][0] << "|" << setw(3) << grid[1][1] << "|" << setw(3)
         << grid[1][2] << "|\n";
    cout << "---+---+---+---|\n";
    cout << "0  |" << setw(3) << grid[0][0] << "|" << setw(3) << grid[0][1] << "|" << setw(3)
         << grid[0][2] << "|\n";
    cout << "---+---+---+---|\n";
    cout << "   | 0 | 1 | 2 |\n";
}

void clearBoard()
{
    // for (int a = 0; a < 3; a++) {
    for (auto &a : grid) {
        for (char &b : a) {
            b = ' ';
        }
    }
}

bool gameOver()
{
    // rows
    if ((grid[0][0] == grid[0][1]) && (grid[0][1] == grid[0][2]) && (grid[0][1]) != ' ') {
        return true;
    } else if ((grid[1][0] == grid[1][1]) && (grid[1][1] == grid[1][2]) && (grid[1][1]) != ' ') {
        return true;
    } else if ((grid[2][0] == grid[2][1]) && (grid[2][1] == grid[2][2]) && (grid[2][1]) != ' ') {
        return true;
    }
    // columns
    else if ((grid[0][0] == grid[1][0]) && (grid[1][0] == grid[2][0]) && (grid[2][0]) != ' ') {
        return true;
    } else if ((grid[0][1] == grid[1][1]) && (grid[1][1] == grid[2][1]) && (grid[2][1]) != ' ') {
        return true;
    } else if ((grid[0][2] == grid[1][2]) && (grid[1][2] == grid[2][2]) && (grid[2][2]) != ' ') {
        return true;
    }
    // diagonal
    else if ((grid[0][0] == grid[1][1]) && (grid[1][1] == grid[2][2]) && (grid[2][2]) != ' ') {
        return true;
    } else if ((grid[2][0] == grid[1][1]) && (grid[1][1] == grid[0][2]) && (grid[0][2]) != ' ') {
        return true;
    } else if (turns > 7)
        return true;

    return false;
}

void inputCoordinates(string playerNames[2])
{
    int x, y;
    do {
        cout << playerNames[turns % 2] << ", what square would you like (x y):  ";
        cin >> y >> x;
    } while (grid[x][y] != ' ');
    if (turns % 2)
        grid[x][y] = 'O';
    else
        grid[x][y] = 'X';
}

void randomAI()
{
    unsigned x, y;

    do {
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<mt19937::result_type> mark(0, 2);
        x = mark(rng);
        y = mark(rng);
    } while (grid[x][y] != ' '); // Repeat until blank square is found

    if (turns % 2)
        grid[x][y] = 'O';
    else
        grid[x][y] = 'X';
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}