#include <iostream>
#include <conio.h>  // For Windows, use <ncurses.h> for Linux
#include <windows.h>
#include <cstdlib>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = std::rand() % width;
    fruitY = std::rand() % height;
    score = 0;
    nTail = 0;
}

void Draw() {
    // Use "cls" for Windows and "clear" for Linux
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                std::cout << "#";
            if (i == y && j == x)
                std::cout << "O";
            else if (i == fruitY && j == fruitX)
                std::cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        std::cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    std::cout << " ";
            }

            if (j == width - 1)
                std::cout << "#";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;
    std::cout << "Score: " << score << std::endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}


void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = std::rand() % width;
        fruitY = std::rand() % height;
        nTail++;
    }
}

void ShowMenu() {
    std::cout << "====================" << endl;
    std::cout << "      SNAKE GAME    " << endl;
    std::cout << "====================" << endl;
    std::cout << "1. Start Game" << endl;
    std::cout << "2. Instructions" << endl;
    std::cout << "3. Exit" << endl;
    std::cout << "Enter your choice: ";
}

void Instructions() {
    std::cout << "====================" << endl;
    std::cout << "    INSTRUCTIONS    " << endl;
    std::cout << "====================" << endl;
    std::cout << "Use 'W' to move up" << endl;
    std::cout << "Use 'S' to move down" << endl;
    std::cout << "Use 'A' to move left" << endl;
    std::cout << "Use 'D' to move right" << endl;
    std::cout << "Press 'X' to exit the game" << endl;
    std::cout << "Press any key to go back to menu..." << endl;
    _getch();
}

int main() {
    std::srand(static_cast<unsigned>(std::time(0))); // Seed the random number generator
    int choice;
    while (true) {
        ShowMenu();
        std::cin >> choice;
        switch (choice) {
        case 1:
            Setup();
            while (!gameOver) {
                Draw();
                Input();
                Logic();
                Sleep(100);  // Sleep(10) for faster game, Sleep(200) for slower
            }
            break;
        case 2:
            Instructions();
            break;
        case 3:
            return 0;
        default:
            std::cout << "Invalid choice! Please try again." << endl;
            break;
        }
    }
    return 0;
}
