﻿#include <iostream>
#include <thread>
#include <vector>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <string>

using namespace std;

int nFieldWidth = 12;
int nFieldHeight = 18;

int nScreenWidth = 120;
int nScreenHeight = 30;

const int xStartPosition = 50;
wstring pieces[7];

wchar_t* pField = nullptr;

// From good old internet
enum
{
	BLACK = 0,
	DARKBLUE = FOREGROUND_BLUE,
	DARKGREEN = FOREGROUND_GREEN,
	DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
	DARKRED = FOREGROUND_RED,
	DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
	DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
	DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	GRAY = FOREGROUND_INTENSITY,
	BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
	RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
	MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
};

WORD displayColor[] = { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE };

bool colorSelection(WORD newColor)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStdOut != INVALID_HANDLE_VALUE)
		return SetConsoleTextAttribute(hStdOut, newColor);

	return false;
}

//from good old internet
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


void Logo()
{
	colorSelection(YELLOW);
	cout << R"(
		  ____ ____ _  _ ____ ____ ___  _ _  _ ____ ____ ____ . ____    ___  ____ ___ ____ 
		  [__  |    |__| |__/ |  | |  \ | |\ | | __ |___ |__/ ' [__     |__] |___  |  [__  
		  ___] |___ |  | |  \ |__| |__/ | | \| |__] |___ |  \   ___]    |    |___  |  ___] 
                                                                                       
)" << '\n';
}

void helpLogo()
{
	colorSelection(YELLOW);
	cout << R"(
						_  _ ____ _    ___  
						|__| |___ |    |__] 
						|  | |___ |___ |    
                                                                                                                                                                 
)" << '\n';
}

void settingsLogo()
{
	colorSelection(YELLOW);
	cout << R"(
				____ ____ ___ ___ _ _  _ ____ ____ 
				[__  |___  |   |  | |\ | | __ [__  
				___] |___  |   |  | | \| |__] ___] 
                                                                                                                
)" << '\n';
}

void game();
void GeneratePieces();
void helpMenu();
void settingsMenu();

void mainMenu()
{
	Logo();

	int counter = 1;
	char key;

	for (;;)
	{
		if (counter >= 1 && counter <= 4)
		{
			displayColor[counter - 1] = RED;
		}

		gotoxy(xStartPosition, 5);
		colorSelection(displayColor[0]);
		cout << "1. Start";

		gotoxy(xStartPosition, 6);
		colorSelection(displayColor[1]);
		cout << "2. Help";

		gotoxy(xStartPosition, 7);
		colorSelection(displayColor[2]);
		cout << "3. Settings";

		gotoxy(xStartPosition, 8);
		colorSelection(displayColor[3]);
		cout << "4. Exit";

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 4)) // 72 - up arrow (keyboard)
			counter--;
		if (key == 80 && (counter >= 1 && counter <= 3)) // 80 - down arrow (keyboard)
			counter++;

		//carriage return - enter (keyboard)
		if (key == '\r')
		{
			for (int i = 0; i < 4; i++)
				displayColor[i] = WHITE;

			system("CLS");

			if (counter == 1)
			{
				game();
				break;
			}
			else if (counter == 2)
			{
				helpMenu();
				break;
			}
			else if (counter == 3)
			{
				settingsMenu();
				break;
			}
			else if (counter == 4)
			{
				break;
			}
		}
		for (int i = 0; i < 4; i++)
			displayColor[i] = WHITE;
	}
}

void helpMenu()
{
	helpLogo();

	int counter = 1;
	char key;

	for (int i = 0;;)
	{
		if (counter == 1) { displayColor[0] = RED; }

		colorSelection(GREEN);
		gotoxy(25, 5);
		cout << "  Controls:" << endl;
		gotoxy(25, 6);
		cout << "  Right arrow: Move the tetromino to the right by 1 block!" << endl;
		gotoxy(25, 7);
		cout << "  Left arrow: Move the tetromino to the left by 1 block!" << endl;
		gotoxy(25, 8);
		cout << "  Down arrow: Drop the tetromino down by 1 block! " << endl;
		gotoxy(25, 9);
		cout << "  Up arrow: Rotate the tetromino by 90*!";

		gotoxy(xStartPosition, 11);
		colorSelection(displayColor[0]);
		cout << "		  Go Back";

		key = _getch();

		//carriage return - enter (keyboard)
		if (key == '\r')
		{
			displayColor[0] = WHITE;

			system("CLS");

			if (counter == 1)
			{
				mainMenu();
				break;
			}
		}
		displayColor[0] = WHITE;
	}
}

void settingsMenu()
{
	settingsLogo();

	int counter = 1;
	char key;

	for (int i = 0;;)
	{
		if (counter == 1) { displayColor[0] = RED; }
		if (counter == 2) { displayColor[1] = RED; }
		if (counter == 3) { displayColor[2] = RED; }
		if (counter == 4) { displayColor[3] = RED; }

		gotoxy(xStartPosition, 5);
		colorSelection(displayColor[0]);
		cout << "1. Start";

		gotoxy(xStartPosition, 6);
		colorSelection(displayColor[1]);
		cout << "2. Help";

		gotoxy(xStartPosition, 7);
		colorSelection(displayColor[2]);
		cout << "3. Settings";

		gotoxy(xStartPosition, 8);
		colorSelection(displayColor[3]);
		cout << "4. Exit";

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 4)) // 72 - up arrow (keyboard)
			counter--;
		if (key == 80 && (counter >= 1 && counter <= 3)) // 80 - down arrow (keyboard)
			counter++;

		//carriage return - enter (keyboard)
		if (key == '\r')
		{
			for (int i = 0; i < 4; i++)
				displayColor[i] = WHITE;

			system("CLS");

			if (counter == 1)
			{
				game();
				break;
			}
			else if (counter == 2)
			{
				helpMenu();
				break;
			}
			else if (counter == 3)
			{

			}
			else if (counter == 4)
			{
				break;
			}
		}
		for (int i = 0; i < 4; i++)
			displayColor[i] = WHITE;
	}
}

int Rotate(int px, int py, int r)
{
	int pi = 0;

	switch (r % 4)
	{
	case 0: // 0 degrees
	{
		pi = py * 4 + px;
		break;
	}

	case 1: // 90 degrees	
	{
		pi = 12 + py - (px * 4);
		break;
	}

	case 2: // 180 degrees
	{
		pi = 15 - (py * 4) - px;
		break;
	}

	case 3: // 270 degrees	
	{
		pi = 3 - py + (px * 4);
		break;
	}
	}

	return pi;
}

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
	for (int px = 0; px < 4; px++)
	{
		for (int py = 0; py < 4; py++)
		{
			// Get index into piece
			int pi = Rotate(px, py, nRotation);

			//Index enters the field
			int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

			// Check if the current block is in bounds
			if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
			{
				if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
				{
					// Do collision check
					if (pieces[nTetromino][pi] != L'.' && pField[fi] != 0)
						return false;
				}
			}
		}
	}

	return true;
}

void game()
{
	colorSelection(RED);

	// Create Screen Buffer
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];

	for (int i = 0; i < nScreenWidth * nScreenHeight; i++)
		screen[i] = L' ';

	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);

	DWORD dwBytesWritten = 0;

	// Create assets
	GeneratePieces();

	// Create play field buffer
	pField = new wchar_t[nFieldWidth * nFieldHeight];

	// Board Boundary
	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y = 0; y < nFieldHeight; y++)
			pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;
	}

	bool bKey[4];
	int nCurrentPiece = rand() % 7;
	int nCurrentRotation = 0;
	int nCurrentX = rand() % 5 + 1;
	int nCurrentY = 0;
	int nSpeed = 20;
	int nSpeedCount = 0;
	bool bForceDown = false;
	bool bRotateHold = true;
	int nPieceCount = 0;
	int nScore = 0;
	vector<int> vLines;
	bool bGameOver = false;

	// Main Loop
	while (!bGameOver)
	{
		// Timing

		// Small Step = 1 Game Tick
		this_thread::sleep_for(50ms);
		nSpeedCount++;
		bForceDown = (nSpeedCount == nSpeed);

		// Player Input
		for (int k = 0; k < 4; k++)
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28\x26"[k]))) != 0;

		// Player Movement
		nCurrentX += (bKey[0] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) ? 1 : 0;
		nCurrentX -= (bKey[1] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) ? 1 : 0;
		nCurrentY += (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) ? 1 : 0;

		// Prevent uncontrollable rotation from holding rotate button
		if (bKey[3])
		{
			nCurrentRotation += (bRotateHold && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;
			bRotateHold = false;
		}
		else
			bRotateHold = true;

		// Force the piece down the playfield if it's time
		if (bForceDown)
		{
			// Update difficulty every 50 pieces

			nSpeedCount = 0;
			nPieceCount++;

			if (nPieceCount % 50 == 0)
			{
				if (nSpeed >= 10)
					nSpeed--;
			}

			// Test if piece can be moved down
			if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
				nCurrentY++;

			else
			{
				// Lock the piece in place
				for (int px = 0; px < 4; px++)
				{
					for (int py = 0; py < 4; py++)
					{
						if (pieces[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
							pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;
					}
				}

				// Check for lines
				for (int py = 0; py < 4; py++)
				{
					if (nCurrentY + py < nFieldHeight - 1)
					{
						bool bLine = true;

						for (int px = 1; px < nFieldWidth - 1; px++)
							bLine &= (pField[(nCurrentY + py) * nFieldWidth + px]) != 0;

						if (bLine == true)
						{
							// Remove Line, set to "="
							for (int px = 1; px < nFieldWidth - 1; px++)
							{
								pField[(nCurrentY + py) * nFieldWidth + px] = 8;
							}
							vLines.push_back(nCurrentY + py);
						}
					}
				}
				if (!vLines.empty())
					nScore += (1 << vLines.size() * 2);

				// Pick a new piece
				nCurrentX = rand() % 5 + 1;
				nCurrentY = 0;
				nCurrentRotation = 0;
				nCurrentPiece = rand() % 7;

				// If the piece doesn't fit straight away, it's game over.
				bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
			}
		}

		// Display

		wchar_t symbols[11] = { L" ABCDEFG=■" };

		// Draw Field
		for (int x = 0; x < nFieldWidth; x++)
		{
			for (int y = 0; y < nFieldHeight; y++)
				screen[(y + 2) * nScreenWidth + (x + 2)] = symbols[pField[y * nFieldWidth + x]];
		}

		// Draw the current piece
		for (int px = 0; px < 4; px++)
		{
			for (int py = 0; py < 4; py++)
			{
				if (pieces[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
					screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;
			}
		}

		// Draw Score
		swprintf_s(&screen[2 * nScreenWidth + nFieldWidth + 6], 16, L"SCORE: %8d", nScore);

		// Gravity - g: 9.8
		// Height - h: 14 - nCurrentY
		// Weight - m: 2
		// Speed - v: 3

		// Kinetic energy: (m * (v * v)) / 2
		// Potencial energy: m * g * h

		// Animate Line Completion
		if (!vLines.empty())
		{
			// Display Frame
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
			// Delay
			this_thread::sleep_for(400ms);

			for (auto& v : vLines)
			{
				for (int px = 1; px < nFieldWidth - 1; px++)
				{
					for (int py = v; py > 0; py--)
						pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];

					pField[px] = 0;
				}
			}

			vLines.clear();
		}

		// Display Frame
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}

	// GameOver
	CloseHandle(hConsole);

	cout << "Game Over! Score:" << nScore << endl;
	Sleep(1000);
	system("CLS");
	mainMenu();
}

void GeneratePieces()
{
	pieces[0].append(L"..X...X...X...X.");
	pieces[0].append(L"..X...X...X...X.");
	pieces[0].append(L"..X...X...X...X.");
	pieces[0].append(L"..X...X...X...X.");

	pieces[1].append(L"..X..XX...X.....");
	pieces[1].append(L"..X..XX...X.....");
	pieces[1].append(L"..X..XX...X.....");
	pieces[1].append(L"..X..XX...X.....");

	pieces[2].append(L".....XX..XX.....");
	pieces[2].append(L".....XX..XX.....");
	pieces[2].append(L".....XX..XX.....");
	pieces[2].append(L".....XX..XX.....");

	pieces[3].append(L"..X..XX..X......");
	pieces[3].append(L"..X..XX..X......");
	pieces[3].append(L"..X..XX..X......");
	pieces[3].append(L"..X..XX..X......");

	pieces[4].append(L".X...XX...X.....");
	pieces[4].append(L".X...XX...X.....");
	pieces[4].append(L".X...XX...X.....");
	pieces[4].append(L".X...XX...X.....");

	pieces[5].append(L".X...X...XX.....");
	pieces[5].append(L".X...X...XX.....");
	pieces[5].append(L".X...X...XX.....");
	pieces[5].append(L".X...X...XX.....");

	pieces[6].append(L"..X...X..XX.....");
	pieces[6].append(L"..X...X..XX.....");
	pieces[6].append(L"..X...X..XX.....");
	pieces[6].append(L"..X...X..XX.....");
}

int main()
{
	mainMenu();
	return 0;
}
