#include <iostream>
using namespace std;

int Rotation(int px, int py, int r)
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