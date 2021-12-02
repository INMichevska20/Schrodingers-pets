#include <iostream>
#include <thread>
#include <vector>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

int nFieldWidth = 12;
int nFieldHeight = 18;

int nScreenWidth = 120;
int nScreenHeight = 30;

wstring tetromino[7];

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

bool colorSelection(WORD newColor)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStdOut != INVALID_HANDLE_VALUE)
		return SetConsoleTextAttribute(hStdOut, newColor);

	return false;
}

using namespace std;


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
	cout << R"(
		  ____ ____ _  _ ____ ____ ___  _ _  _ ____ ____ ____ . ____    ___  ____ ___ ____ 
		  [__  |    |__| |__/ |  | |  \ | |\ | | __ |___ |__/ ' [__     |__] |___  |  [__  
		  ___] |___ |  | |  \ |__| |__/ | | \| |__] |___ |  \   ___]    |    |___  |  ___] 
                                                                                       
)" << '\n';
}

void mainMenu()
{
	Logo();

	int Set[] = { 7, 7, 7 };
	int counter = 2;
	char key;

	for (int i = 0;;)
	{
		gotoxy(20, 5);
		//color(Set[0]);
		cout << "1. Start";

		gotoxy(20, 6);
		//color(Set[1]);
		cout << "2. Help";

		gotoxy(20, 7);
		//color(Set[2]);
		cout << "3. Settings";

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 3)) // 72 - up arrow (keyboard)
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 2)) // 80 - down arrow (keyboard)
		{
			counter++;
		}
		if (key == '\r') //carriage return - enter (keyboard)
		{
			for (int i = 0; i < 3; i++)
				cout << endl;
			system("CLS");

			if (counter == 1)
			{
				cout << "Menu 1 is open!";
			}
			else if (counter == 2)
			{
				cout << "  Controls:" << endl;
				cout << "  Right arrow: Move the tetromino to the right by 1 block!" << endl;
				cout << "  Left arrow: Move the tetromino to the left by 1 block!" << endl;
				cout << "  Down arrow: Drop the tetromino down by 1 block! " << endl;
				cout << "  Button 'Z': Rotate the tetromino by 90*!";
			}
			else if (counter == 3)
			{
				cout << "Menu 3 is open!";
			}
		}

		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;

		if (counter == 1)
		{
			Set[0] = 12;
		}

		if (counter == 2)
		{
			Set[1] = 12;
		}

		if (counter == 3)
		{
			Set[2] = 12;
		}

	}
}

void helpMenu()
{
	Logo();

	int Set[] = { 7, 7, 7 };
	int counter = 2;
	char key;

	for (int i = 0;;)
	{
		gotoxy(20, 6);
		//color(Set[1]);
		cout << "2. Help";

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 3)) // 72 - up arrow (keyboard)
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 2)) // 80 - down arrow (keyboard)
		{
			counter++;
		}
		if (key == '\r') //carriage return - enter (keyboard)
		{
			for (int i = 0; i < 3; i++)
				cout << endl;
			system("CLS");

			if (counter == 1)
			{
				cout << "  Menu 1 is open!";
			}
			else if (counter == 2)
			{
				cout << "  Controls:" << endl;
				cout << "  Right arrow: Move the tetromino to the right by 1 block!" << endl;
				cout << "  Left arrow: Move the tetromino to the left by 1 block!" << endl;
				cout << "  Down arrow: Drop the tetromino down by 1 block! " << endl;
				cout << "  Button 'Z': Rotate the tetromino by 90*!";
			}
			else if (counter == 3)
			{
				cout << "  Menu 3 is open!";
			}
		}

		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;

		if (counter == 1)
		{
			Set[0] = 12;
		}

		if (counter == 2)
		{
			Set[1] = 12;
		}

		if (counter == 3)
		{
			Set[2] = 12;
		}

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
					if (tetromino[nTetromino][pi] != L'.' && pField[fi] != 0)
						return false;
				}
			}
		}
	}

	return true;
}

int main()
{
	mainMenu();
	colorSelection(RED);

	// Create Screen Buffer
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];

	for (int i = 0; i < nScreenWidth * nScreenHeight; i++)
		screen[i] = L' ';

	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);

	DWORD dwBytesWritten = 0;

	// Create assets
	tetromino[0].append(L"..X...X...X...X.");
	tetromino[0].append(L"..X...X...X...X.");
	tetromino[0].append(L"..X...X...X...X.");
	tetromino[0].append(L"..X...X...X...X.");

	tetromino[1].append(L"..X..XX...X.....");
	tetromino[1].append(L"..X..XX...X.....");
	tetromino[1].append(L"..X..XX...X.....");
	tetromino[1].append(L"..X..XX...X.....");

	tetromino[2].append(L".....XX..XX.....");
	tetromino[2].append(L".....XX..XX.....");
	tetromino[2].append(L".....XX..XX.....");
	tetromino[2].append(L".....XX..XX.....");

	tetromino[3].append(L"..X..XX..X......");
	tetromino[3].append(L"..X..XX..X......");
	tetromino[3].append(L"..X..XX..X......");
	tetromino[3].append(L"..X..XX..X......");

	tetromino[4].append(L".X...XX...X.....");
	tetromino[4].append(L".X...XX...X.....");
	tetromino[4].append(L".X...XX...X.....");
	tetromino[4].append(L".X...XX...X.....");

	tetromino[5].append(L".X...X...XX.....");
	tetromino[5].append(L".X...X...XX.....");
	tetromino[5].append(L".X...X...XX.....");
	tetromino[5].append(L".X...X...XX.....");

	tetromino[6].append(L"..X...X..XX.....");
	tetromino[6].append(L"..X...X..XX.....");
	tetromino[6].append(L"..X...X..XX.....");
	tetromino[6].append(L"..X...X..XX.....");

	// Create play field buffer
	pField = new wchar_t[nFieldWidth * nFieldHeight];

	// Board Boundary
	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y = 0; y < nFieldHeight; y++)
			pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;
	}

	bool bKey[4];
	int nCurrentPiece = 0;
	int nCurrentRotation = 0;
	int nCurrentX = nFieldWidth / 2;
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
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;

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
						if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
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

								vLines.push_back(nCurrentY + py);
							}
						}
					}
				}
				//nScore += 25;
				if (!vLines.empty())
					nScore += (1 << vLines.size());

				// Pick a new piece
				nCurrentX = nFieldWidth / 2;
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
				if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
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

	system("pause");
	return 0;
}
