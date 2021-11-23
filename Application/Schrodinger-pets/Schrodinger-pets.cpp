#include <iostream>
#include <cstring>

using namespace std;

int nScreenWidth = 120;
int nScreenHeight = 30;

int nFieldWidth = 12;
int nFieldHeight = 18;

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

            int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

            if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
            {
                if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
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


    int nCurrentPiece = 0;
    int nCurrentRotation = 0;
    int nCurrentX = nFieldWidth / 2;
    int nCurrentY = 0;
    int nSpeedCount = 0;
    int bForceDown = 0;
    int nSpeed = 20;
    int nPieceCount = 0;
    bool bGameOver = false;
    bool bKey[4];
    bool bRotateHold = true;
    bool bForceDown = false;


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

        // Player Movement

        nCurrentX += (bKey[0] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) ? 1 : 0;
        nCurrentX -= (bKey[1] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) ? 1 : 0;
        nCurrentY += (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) ? 1 : 0;

        // Prevent uncontrollable rotation from holding rotate button

        if (bKey[3])
        {
            nCurrentRotation += (bRotateHold && DoesPieceFit(nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;
            bRotateHold = false;

        }
        else
        {
            bRotateHold = true;
        }
 
        // Force a piece down automatically

        if (bForceDown)
        {
            // Update difficulty every 50 pieces

            nSpeedCount = 0;
            nPieceCount++;

            if (nPieceCount % 50 == 0)
            {
                if (nSpeed >= 10)
                {
                    nSpeed--;
                }

            }

            // Check if piece can be moved down

            if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
            {
                nCurrentY++;

            }
            else // If it can't, lock the piece in place 
            {
                for (int px = 0; px < 4; px++)
                {
                    for (int py = 0; py < 4; py++)
                    {
                        if (tetromino[nCurrentPiece][Rotation(px, py, nCurrentRotation)] != L'.')
                        {
                            pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;
                        }
                    }
                }

            }

        }


    }

}