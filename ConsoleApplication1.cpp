#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;
enum {
	RightUp,
	RightDown,
	LeftUp,
	LeftDown,
	Over
};
void hui(int map[20][20]) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++)
		{
			if (map[i][j] == 0) {
				cout << "  ";
			}
			else if (map[i][j] == 4 || map[i][j] == 5) {
				cout << "■";
			}
			else if (map[i][j] == 3) {
				cout << "★";
			}
			else if (map[i][j] == 2) {
				cout << "〓";
			}
			else if (map[i][j] == 1)
			{
				cout << "●";
			}
		}
		cout << endl;
	}
}
void move(COORD& ball, int cx, int cy, int map[20][20], int& Gstate) {
	map[ball.X][ball.Y] = 0;
	ball.X += cx;
	ball.Y += cy;
	if (ball.Y == 19 && Gstate == RightDown) {
		ball.Y--;
		ball.X--;
		Gstate = LeftDown;
	}
	else if (ball.Y == 19 && Gstate == RightUp)
	{
		ball.Y--;
		ball.X++;
		Gstate = LeftUp;
	}
	else if (ball.Y == 0 && Gstate == LeftUp)
	{
		ball.Y++;
		ball.X++;
		Gstate = RightUp;
	}
	else if (ball.Y == 0 && Gstate == LeftDown)
	{
		ball.Y++;
		ball.X--;
		Gstate = RightDown;
	}
	else if (ball.X == 0 && Gstate == RightUp)
	{
		ball.X++;
		ball.Y--;
		Gstate = RightDown;
	}
	else if (ball.X == 0 && Gstate == LeftUp)
	{
		ball.X++;
		ball.Y++;
		Gstate = LeftDown;
	}
	else if (map[ball.X][ball.Y] == 3 && Gstate == LeftUp)
	{
		map[ball.X][ball.Y + 1] = 0;
		ball.X++;
		ball.Y++;
		Gstate = LeftDown;
	}
	else if (map[ball.X][ball.Y - 1] == 3 && Gstate == RightUp)
	{
		map[ball.X][ball.Y - 1] = 0;
		ball.X++;
		ball.Y--;
		Gstate = RightDown;
	}
	else if (map[ball.X][ball.Y] == 2 && Gstate == LeftDown)
	{
		ball.X--;
		ball.Y++;
		Gstate = LeftUp;
	}
	else if (map[ball.X][ball.Y] == 2 && Gstate == RightDown)
	{
		ball.X--;
		ball.Y--;
		Gstate = RightUp;
	}
	else if (ball.X == 19)
	{
		ball.X--;
		Gstate = Over;
	}
	map[ball.X][ball.Y] = 1;
}
void minego(COORD& mine, int sy, int map[20][20]) {
	for (int i = mine.X; i <= mine.Y; i++) {
		map[18][i] = 0;
	}
	mine.X += sy;
	mine.Y += sy;
	if (mine.X > 0 && mine.Y < 19) {
		for (int i = mine.X; i <= mine.Y; i++) {
			map[18][i] = 2;
		}
	}
	else
	{
		mine.X -= sy;
		mine.Y -= sy;
		for (int i = mine.X; i <= mine.Y; i++) {
			map[18][i] = 2;
		}
	}
}
void main() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);// Get the console cursor information
	CursorInfo.bVisible = false; // hide the console cursor
	SetConsoleCursorInfo(handle, &CursorInfo);
	int map[20][20] = {};
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++)
		{
			if (i == 0 || j == 0 || j == 19) {
				map[i][j] = 5;
			}
			else if (i == 19) {
				map[i][j] = 4;
			}
			else if (i < 4) {
				map[i][j] = 3;
			}
		}
	}
	COORD ball = { 17, 10 };
	COORD mine = { 9, 11 };
	map[ball.X][ball.Y] = 1;
	for (int i = mine.X; i <= mine.Y; i++) {
		map[18][i] = 2;
	}
	hui(map);
	int Gstate = RightUp;
	HANDLE hOutput;
	COORD coord = { 0, 0 };
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	// create a new buffer
	HANDLE hOutBuf = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);

	// set new buffer display buffer for the active
	SetConsoleActiveScreenBuffer(hOutBuf);

	// hide the cursor two buffers
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);
	SetConsoleCursorInfo(hOutBuf, &cci);

	// double buffering display
	DWORD bytes = 100;
	char data[1600];
	while (Gstate != Over)
	{
		ReadConsoleOutputCharacterA(hOutput, data, 1600, coord, &bytes);
		WriteConsoleOutputCharacterA(hOutBuf, data, 1600, coord, &bytes);
		system("cls");
		hui(map);
		Sleep(100);
		char Control;
		if (_kbhit())
		{
			Control = _getch();
			switch (Control)
			{
			case 'a':minego(mine, -1, map); break;
			case 'd':minego(mine, 1, map); break;
			default:
				break;
			}
		}
		switch (Gstate)
		{
		case RightUp:move(ball, -1, 1, map, Gstate); break;
		case RightDown:move(ball, 1, 1, map, Gstate); break;
		case LeftUp:move(ball, -1, -1, map, Gstate); break;
		case LeftDown:move(ball, 1, -1, map, Gstate); break;
		default:
			break;
		}

	}
	ReadConsoleOutputCharacterA(hOutput, data, 1600, coord, &bytes);
	WriteConsoleOutputCharacterA(hOutBuf, data, 1600, coord, &bytes);
	cout << "game over" << endl;
	system("pause");
}