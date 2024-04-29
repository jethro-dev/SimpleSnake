#include <vector>
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
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
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	nTail = 0;
}

void Draw() {

	system("cls"); // system("clear"); on Linux

	// Draw the top row
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	// Draw the default rows
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	// Draw the bottom row
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
	cout << "Tails: " << nTail << endl;

}

void Input() {
	// Check if keyboard is hit
	if (_kbhit()) {
		switch (_getch()) {
			case 'w':
				dir = UP;
				break;
			case 'a':
				dir = LEFT;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'd':
				dir = RIGHT;
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
	}

	// Wrap snake position on reaching border
	if (x < 1) x = width; else if (x > width) x = 1;
	if (y < 0) y = height -1; else if (y > height - 1) y = 0;
	

	// When we eat a fruit
	if (x == fruitX && y == fruitY) {
		nTail++;
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
	}

}

int main() {

	Setup();

	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(100);
	}

	return 0;
}