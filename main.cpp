/*This is a TicTacToe Program with a HighScores list.  It is text-based,
It has been coded to run and compile under Windows,
but should not require much change to comile under *nix-based systems.  Simpply
#include <dose.h> to #include <time.h> and the calls to system("cls") to
system("clear");, and it should work.  I do not want to write ifdefs for these.
The qsort.h file that I am using is under the LGPL license, please read the
license included in that file.*/

#include "qsort.h"
#include <iostream>
#include <stdlib.h>
#ifdef _WIN32 // includes dos.h only when
#include <dos.h> //using the Windows
#else // enviroment [used for sleep()]
#include <time.h> //used for sleep() on *NIX-based systems
#endif

#include <fstream>
#include <iomanip>
#include <string>

using namespace std;
void int_qsort(int* arr, unsigned); // ProtoType for qsort
void newGame();
void ShowHighScores();
void DeteminWinner();
void drawBoard1();
void drawBoard2();
void highScores();
void EasyAI();
void inputCordnates1();
void inputCordnates2();
void resetHighScores();

bool p2 = true;
bool wonX;
bool wonO;
bool rerun = true;
int AItype, taken, players;
double score;
string player[2];
char x[3][3];
int main()
{
    int ans; // Holds menu choice
    // insert code here...
    while (rerun) {
        taken = 0;
        AItype = 0;
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        // if no highscores list excist, create on withthe default values
        fstream test;
        test.open("highscores.txt");
        if (!test)
            resetHighScores();
        test.close();
        cout << "What would you like to do?\n" << endl;
        cout << "\n1.  Start a new game of TicTacToe...";
        cout << "\n2.  View highscores...";
        cout << "\n3.  Reset the High-Scores";
        cout << "\n4.  Exit\n\n";
        // sleep(1);
        cin >> ans;

        switch (ans) {
        case 1:
            newGame();
            break;

        case 2:
            ShowHighScores();
            break;

        case 3:
            resetHighScores();
            break;

        case 4:
            rerun = false;
            break;

        default:
            break;
        }
    }
    // std::cout << "Hello, World!\n";
    return 0;
}
void newGame()
{

    wonX = false;
    wonO = false;

    if (wonX || wonO)
        return;

    for (int cnt = 1; cnt < 4; cnt++) {
        for (int count = 0; count < 3; count++) {
            x[cnt][count] = ' ';
        }
    }

    cout << "\n\nWould you like to play a one or a two player game? (1/2)\n";
    cin >> players;
    cout << "\nPlayer 1, Enter your name:  ";
    cin.ignore();
    getline(cin, player[0]);
    if (players == 2) {
        cout << "\nPlayer 2, Enter your name:  ";
        cin.ignore();
        getline(cin, player[1]);
    } else if (players == 1) {
        p2 = false;
        cout << "What strength of AI do you want to play against (1. Easy 2. Hard)";
        cin >> AItype;
        player[1] = "Computer";
    }
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    drawBoard1();
}
/*he Easy AI function, this AI has no intellegence, it puts a mark in the first available square*/
void EasyAI()
{
    if (wonX || wonO)
        return;

    for (int cnt = 1; cnt < 4; cnt++) {
        for (int count = 0; count < 3; count++) {
            if (x[cnt][count] == ' ') {
                x[cnt][count] = 'O';
                taken++;
                drawBoard1();
            }
        } // exit the function
    }
}
// This AI has a few if statement, if none of them can be done, it falls back on the EasyAI
void HardAI()
{
    if (wonX || wonO)
        return;

    if (x[2][1] == ' ')
        x[2][1] = 'O';
    else if (x[1][1] == 'X' && x[1][2] == ' ')
        x[1][2] = 'O';
    else if ((x[1][0] == 'X' || x[1][2]) && x[1][1] == ' ')
        x[1][1] = 'O';
    else if (x[3][0] == ' ')
        x[3][0] = 'O';
    else if (x[1][0] == ' ')
        x[1][0] = 'O';
    else if (x[2][0] == ' ')
        x[2][0] = 'O';
    else if (x[1][2] == ' ')
        x[1][2] = 'O';
    else if (x[1][1] == ' ')
        x[1][1] = 'O';
    else
        for (int cnt = 1; cnt < 4; cnt++) {
            for (int count = 0; count < 3; count++) {
                if (x[cnt][count] == ' ') {
                    x[cnt][count] = 'O';
                    taken++;
                    drawBoard1();
                }
            } // exit the function
        }
    taken++;
    drawBoard1();
}

void inputCordnates1()
{
    int xc, yc;
    bool valid = false;

    if (wonX || wonO)
        return;

    while (!valid) {
        cout << player[0] << " what column do you want to place your X in:  ";
        cin >> xc;
        cout << player[0] << " what row do you want to place your X in:  ";
        cin >> yc;
        if (x[yc][xc - 1] != ' ')
            drawBoard2();
        else {
            valid = true;
            x[yc][xc - 1] = 'X';
        }
    }

    taken++;
    drawBoard2();

    if (AItype == 1)
        EasyAI();
    else if (AItype == 2)
        HardAI();
    if (players == 2)
        inputCordnates2();
}
void drawBoard1()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    cout << "   | 1 | 2 | 3 |\n";
    cout << "---+---+---+---|\n";
    cout << "1  |" << setw(3) << x[1][0] << "|" << setw(3) << x[1][1] << "|" << setw(3) << x[1][2]
         << "|\n";
    cout << "---+---+---+---|\n";
    cout << "2  |" << setw(3) << x[2][0] << "|" << setw(3) << x[2][1] << "|" << setw(3) << x[2][2]
         << "|\n";
    cout << "---+---+---+---|\n";
    cout << "3  |" << setw(3) << x[3][0] << "|" << setw(3) << x[3][1] << "|" << setw(3) << x[3][2]
         << "|\n";
    cout << "---+---+---+---|\n\n\n";

    DeteminWinner();
    if (!wonX || !wonO)
        inputCordnates1();
}
void drawBoard2()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    cout << "   | 1 | 2 | 3 |\n";
    cout << "---+---+---+---|\n";
    cout << "1  |" << setw(3) << x[1][0] << "|" << setw(3) << x[1][1] << "|" << setw(3) << x[1][2]
         << "|\n";
    cout << "---+---+---+---|\n";
    cout << "2  |" << setw(3) << x[2][0] << "|" << setw(3) << x[2][1] << "|" << setw(3) << x[2][2]
         << "|\n";
    cout << "---+---+---+---|\n";
    cout << "3  |" << setw(3) << x[3][0] << "|" << setw(3) << x[3][1] << "|" << setw(3) << x[3][2]
         << "|\n";
    cout << "---+---+---+---|\n\n\n";

    DeteminWinner();
}
void inputCordnates2()
{
    int xc, yc;
    bool valid = false;

    if (wonX || wonO)
        return;

    while (!valid) {
        cout << player[1] << " what column do you want to place your O in:  ";
        cin >> xc;
        cout << player[1] << " what row do you want to place your O in:  ";
        cin >> yc;
        if (x[yc][xc - 1] != ' ')
            drawBoard2();
        else {
            valid = true;
            x[yc][xc - 1] = 'O';
        }
    }

    taken++;
    drawBoard1();
}
void DeteminWinner() // The program is getting stuck if ANY of thes are true
{
    if (wonX || wonO)
        return;

    if (x[1][0] == 'X' && x[1][1] == 'X' && x[1][2] == 'X') { // across line 1
        wonX = true;
        highScores();
    } else if (x[2][0] == 'X' && x[2][1] == 'X' && x[2][2] == 'X') { // across line 2
        wonX = true;
        highScores();
    } else if (x[3][0] == 'X' && x[3][1] == 'X' && x[3][2] == 'X') { // across line 3
        wonX = true;
        highScores();
    } else if (x[1][0] == 'X' && x[2][1] == 'X' && x[3][2] == 'X') { // diagnal top-left
        wonX = true;
        highScores();
    } else if (x[1][2] == 'X' && x[2][1] == 'X' && x[3][0] == 'X') { // diagnal top-right
        wonX = true;
        highScores();
    } else if (x[1][0] == 'X' && x[2][0] == 'X' && x[3][0] == 'X') { // down column 1
        wonX = true;
        highScores();
    } else if (x[1][1] == 'X' && x[2][1] == 'X' && x[3][1] == 'X') { // down column 2
        wonX = true;
        highScores();
    } else if (x[1][2] == 'X' && x[2][2] == 'X' && x[3][2] == 'X') { // down column 3
        wonX = true;
        highScores();
    }

    else if (x[1][0] == 'O' && x[1][1] == 'O' && x[1][2] == 'O') { // across line 1
        wonO = true;
        highScores();
    } else if (x[2][0] == 'O' && x[2][1] == 'O' && x[2][2] == 'O') { // across line 2
        wonO = true;
        highScores();
    } else if (x[3][0] == 'O' && x[3][1] == 'O' && x[3][2] == 'O') { // across line 3
        wonO = true;
        highScores();
    } else if (x[1][0] == 'O' && x[2][1] == 'O' && x[3][2] == 'O') { // diagnal top-left
        wonO = true;
        highScores();
    } else if (x[1][2] == 'O' && x[2][1] == 'O' && x[3][0] == 'O') { // diagnal top-right
        wonO = true;
        highScores();
    } else if (x[1][0] == 'O' && x[2][0] == 'O' && x[3][0] == 'O') { // down column 1
        wonO = true;
        highScores();
    } else if (x[1][1] == 'O' && x[2][1] == 'O' && x[3][1] == 'O') { // down column 2
        wonO = true;
        highScores();
    } else if (x[1][2] == 'O' && x[2][2] == 'O' && x[3][2] == 'O') { // down column 3
        wonO = true;
        highScores();
    } else if (taken == 9) {
        wonO = true;
        wonX = true;
        cout << "The game has been tied\n";
        cin.ignore();
        cin.get();
        return;
    }
}
void highScores()
{
    int num = 0, size = 11;
    int scores[11];

    if (wonX) {
        for (int cnt = 1; cnt < 4; cnt++) {
            for (int count = 0; count < 3; count++) {
                if (x[cnt][count] == 'X')
                    num++;
            }
        }
        cout << player[0] << " won in " << num << " moves";
    }

    else if (wonO) {
        for (int cnt = 1; cnt < 4; cnt++) {
            for (int count = 0; count < 3; count++) {
                if (x[cnt][count] == 'O')
                    num++;
            }
        }
        cout << player[1] << " won in " << num << " moves";
    }

    fstream infile;
    infile.open("highscores.txt");

    for (int count = 0; count < 10 || !infile.eof(); count++) {
        infile >> scores[count];
    }
    infile.close();

    scores[10] = num;
    int_qsort(scores, size); // Call funtion to sort in ascending order

    ofstream outfile;
    outfile.open("highscores.txt");
    for (int count = 0; count < 10; count++) // I only want 10 highscores saved
        outfile << scores[count] << " ";
    outfile.close();
    ShowHighScores();
}
void int_qsort(int* arr, unsigned n) // The sorting function
{
#define int_lt(a, b) ((*a) < (*b))
    QSORT(int, arr, n, int_lt);
}
void ShowHighScores()
{
    int score, count = 0;

    ifstream infile;
    infile.open("highscores.txt");
    for (int cnt = 0; cnt < 10; cnt++) {
        infile >> score;
        if (score != 99) // 99 is the defaulr NULL value
        {
            cout << "\nA game was won after " << score << " moves";
            count++;
        }
    }
    if (count == 0)
        cout << "There are no High-Scores to display";
    cin.ignore();
    cin.get();
}
void resetHighScores()
{
    ofstream outfile;
    outfile.open("highscores.txt");
    for (int count = 0; count < 10; count++)
        outfile << "99 "; // 99 is the defaulr NULL value
    outfile.close();
}
