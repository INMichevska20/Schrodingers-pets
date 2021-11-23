#include <iostream>
#include <cstring>

using namespace std;

int screenWidth = 120;
int screenHeight = 30;

int fieldWidth = 12;
int fieldHeight = 18;

wstring tetromino[7];

unsigned char* pField = nullptr;

int Rotation (int px, int py, int r)
{
    switch (r % 4)
    {
    case 0: return py * 4 + px;         // 0*
    case 1: return 12 + py - (px * 4);  // 90*
    case 2: return 15 - (py * 4) - px;  // 180*
    case 3: return 3 - py + (px * 4);   // 270*
    }
    return 0;
}

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
    for (int px = 0; px < 4; px++)
    {
        for (int py = 0; py < 4; py++)
        {
            int pi = Rotation(px, py, nRotation);

            int fi = (nPosY + py) * fieldWidth + (nPosX + px);

            if (nPosX + px >= 0 && nPosX + px < fieldWidth)
            {
                if (nPosY + py >= 0 && nPosY + py < fieldHeight)
                {
                    if (tetromino[nTetromino][pi] != L'.' && pField[fi] != 0)
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}


int main()
{
    // create assets
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");

    tetromino[1].append(L"..X.");
    tetromino[1].append(L".XX.");
    tetromino[1].append(L".X..");
    tetromino[1].append(L"....");

    tetromino[2].append(L".X..");
    tetromino[2].append(L".XX.");
    tetromino[2].append(L"..X.");
    tetromino[2].append(L"....");

    tetromino[3].append(L"....");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L"....");

    tetromino[4].append(L"..X.");
    tetromino[4].append(L".XX.");
    tetromino[4].append(L"..X.");
    tetromino[4].append(L"....");

    tetromino[5].append(L"....");
    tetromino[5].append(L".XX.");
    tetromino[5].append(L"..X.");
    tetromino[5].append(L"..X.");

    tetromino[6].append(L"....");
    tetromino[6].append(L".XX.");
    tetromino[6].append(L".X..");
    tetromino[6].append(L".X..");

    int nSpeedCount = 0;
    int bForceDown = 0;
    int nSpeed = 20;
    bool bGameOver = false;
    bool bKey[4];


    while (!bGameOver)
    {
        this_thread::sleep_for(50ms); // 1 Game Tick
        nSpeedCount++;
        bForceDown = (nSpeedCount == nSpeed);

        // Player Input

        for (int k = 0; k < 4; k++)
        {
            bKey[4] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;
        }

        




    }

}