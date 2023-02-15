#include "game.h"
#include <iostream>
#include "../states/game_state.h"

Game::Game()
    //: RESOLUTION(GRID_SIZE*nFieldWidth+3*OFFSET_X, GRID_SIZE*(nFieldHeight+5)+OFFSET_Y)
    : pField(nullptr), RESOLUTION(660, 680)
{
}

sf::String Game::getElementOfPiece(int x, int y)
{
    if(Game::COUNT_OF_BLOCKS == 3)
    {
        return triomino[x][y];
    }
    else if(Game::COUNT_OF_BLOCKS == 4)
    {
        return tetromino[x][y];
    }
    else if(Game::COUNT_OF_BLOCKS == 5)
    {
        return pentomino[x][y];
    }

    return sf::String();
}

sf::String Game::pentomino[] =
{
    //F
    sf::String      ("....."
                     "..XX."
                     ".XX.."
                     "..X.."
                     "....."),
    //RF
    sf::String      ("....."
                     ".XX.."
                     "..XX."
                     "..X.."
                     "....."),
    //I
    sf::String      ("..X.."
                     "..X.."
                     "..X.."
                     "..X.."
                     "..X.."),
    //J
    sf::String      ("..X.."
                     "..X.."
                     "..X.."
                     ".XX.."
                     "....."),
    //N
    sf::String      ("....."
                     ".XX.."
                     "..XXX"
                     "....."
                     "....."),
    //RN
    sf::String      ("....."
                     "..XX."
                     "XXX.."
                     "....."
                     "....."),
    //P
    sf::String      ("....."
                     "..XX."
                     "..XX."
                     "..X.."
                     "....."),
    //RP
    sf::String      ("....."
                     ".XX.."
                     ".XX.."
                     "..X.."
                     "....."),
    //T
    sf::String      ("....."
                     ".XXX."
                     "..X.."
                     "..X.."
                     "....."),
    //V
    sf::String      ("..X.."
                     "..X.."
                     "..XXX"
                     "....."
                     "....."),
    //W
    sf::String       ("....."
                     ".X..."
                     ".XX.."
                     "..XX."
                     "....."),
    //X
    sf::String      ("....."
                     "..X.."
                     ".XXX."
                     "..X.."
                     "....."),
    //Y
    sf::String      ("....."
                     "..X.."
                     "XXXX."
                     "....."
                     "....."),
    //RY
    sf::String      ("....."
                     "....."
                     "XXXX."
                     "..X.."
                     "....."),
    //Z
    sf::String      ("....."
                     ".XX.."
                     "..X.."
                     "..XX."
                     "....."),
    //RZ
    sf::String      ("....."
                     "..XX."
                     "..X.."
                     ".XX.."
                     ".....")
};

sf::String Game::tetromino[] =
{
    //I
    sf::String("..X."
               "..X."
               "..X."
               "..X."),
    //O
    sf::String("...."
               ".XX."
               ".XX."
               "...."),
    //T
    sf::String("...."
               "XXX."
               ".X.."
               "...."),
    //S
    sf::String("...."
               ".XX."
               "XX.."
               "...."),
    //Z
    sf::String("...."
               "XX.."
               ".XX."
               "...."),
    //J
    sf::String(".X.."
               ".X.."
               "XX.."
               "...."),
    //L
    sf::String(".X.."
               ".X.."
               ".XX."
               "....")
};

sf::String Game::triomino[] = {
    //I
    sf::String(".X."
               ".X."
               ".X."),
    //L
    sf::String(".X."
               ".XX"
               "..."),
    //J
    sf::String(".X."
               "XX."
               "...")
};

void Game::initBoard(int level)
{
    std::cout << "initBoard " << level << std::endl;
    if(level == 3)
    {
        setTriomino();
    }
    else if(level == 4)
    {
        setTetromino();
    }
    else if(level == 5)
    {
        setPentomino();
    }
    if(pField)
    {
        delete [] pField;
    }
    pField = new unsigned char[nFieldWidth*nFieldHeight];

    for (int x = 0; x < nFieldWidth; x++) // Board Boundary
    {
        for (int y = 0; y < nFieldHeight; y++)
        {
            pField[y*nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? Game::BOUNDARY_BLOCK : 0;
        }
    }
}

void Game::setPentomino()
{
    OFFSET_X = 100;
    OFFSET_Y = 10;

    COUNT_OF_PIECES = 16;
    nFieldWidth = 13;
    nFieldHeight = 21;
    COUNT_OF_BLOCKS = 5;
}

void Game::setTetromino()
{
    OFFSET_X = 150;
    OFFSET_Y = 30;

    COUNT_OF_PIECES = 7;
    nFieldWidth = 10;
    nFieldHeight = 20;
    COUNT_OF_BLOCKS = 4;
}

void Game::setTriomino()
{
    OFFSET_X = 250;
    OFFSET_Y = 130;
    COUNT_OF_PIECES = 3;
    nFieldWidth = 8;
    nFieldHeight = 15;
    COUNT_OF_BLOCKS = 3;

}

unsigned char *Game::field() const
{
    return pField;
}

int Game::rotate(int px, int py, int r)
{
    int pi = 0;
    if(COUNT_OF_BLOCKS == 3)
    {
        switch(r%4)
        {
        case 0://0
        {
            //0  1   2
            //3  4   5
            //6  7   8
            pi = py * COUNT_OF_BLOCKS + px;
        }
            break;
        case 1://90
        {
            //6  3  0
            //7  4  1
            //8  5  2
            pi = 6 + py - (px * COUNT_OF_BLOCKS);
        }
            break;
        case 2: //180
        {
            //8   7   6
            //5   4   3
            //2   1   0
            pi = 8 - (py * COUNT_OF_BLOCKS) - px;
        }
            break;
        case 3://270
        {

            // 2  5  8
            // 1  4  7
            // 0  3  6
            pi = 2 - py + (px * COUNT_OF_BLOCKS);
        }
            break;
        }
    }
    else if(COUNT_OF_BLOCKS == 4)
    {
        switch(r%4)
        {
        case 0://0
        {
            //0  1   2  3
            //4  5   6  7
            //8  9   10 11
            //12 13  14 15
            pi = py * COUNT_OF_BLOCKS + px;
        }
            break;
        case 1://90
        {
            //  12  8  4  0
            //  13  9  5  1
            //  14 10  6  2
            //  15 11  7  3
            pi = 12 + py - (px * COUNT_OF_BLOCKS);
        }
            break;
        case 2: //180
        {
            // 15  14  13  12
            // 11  10   9   8
            //  7   6   5   4
            //  3   2   1   0
            pi = 15 - (py * COUNT_OF_BLOCKS) - px;
        }
            break;
        case 3://270
        {
            // 3  7  11  15
            // 2  6  10  14
            // 1  5   9  13
            // 0  4   8  12
            pi = 3 - py + (px * COUNT_OF_BLOCKS);
        }
            break;
        }
    }
    else if(COUNT_OF_BLOCKS == 5)
    {
        switch(r%4)
        {
        case 0://0
        {
            //0  1   2  3  4
            //5  6   7  8  9
            //10 11  12 13 14
            //15 16  17 18 19
            //20 21  22 23 24
            pi = py * COUNT_OF_BLOCKS + px;
        }
            break;
        case 1://90
        {
            //20  15 10  5  0
            //21  16 11  6  1
            //22  17 12  7  2
            //23  18 13  8  3
            //24  19 14  9  4
            pi = 20 + py - (px * COUNT_OF_BLOCKS);
        }
            break;
        case 2: //180
        {
            //24   23  22  21  20
            //19   18  17  16  15
            //14   13  12  11  10
            //9     8   7   6   5
            //4     3   2   1   0
            pi = 24 - (py * COUNT_OF_BLOCKS) - px;
        }
            break;
        case 3://270
        {
            // 4  9  14  19  24
            // 3  8  13  18  23
            // 2  7  12  17  22
            // 1  6  11  16  21
            // 0  5  10  15  20
            pi = 4 - py + (px * COUNT_OF_BLOCKS);
        }
            break;
        }
    }
    return pi;
}

bool Game::doesPieceFit(int nTetronimo, int nRotation, int nPosX, int nPosY)
{
    // All Field cells >0 are occupied
    for (int px = 0; px < COUNT_OF_BLOCKS; px++)
        for (int py = 0; py < COUNT_OF_BLOCKS; py++)
        {
            // Get index into piece
            int pi = rotate(px, py, nRotation);

            // Get index into field
            int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

            // Check that test is in bounds. Note out of bounds does
            // not necessarily mean a fail, as the long vertical piece
            // can have cells that lie outside the boundary, so we'll
            // just ignore them
            if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
            {
                if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
                {
                    // In Bounds so do collision check
                    if (getElementOfPiece(nTetronimo, pi) != '.' && pField[fi] != 0)
                        return false; // fail on first hit
                }
            }
        }

    return true;
}


