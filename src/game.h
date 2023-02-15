#ifndef GAME_H
#define GAME_H
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/String.hpp>

class Game
{
public:
    Game();
    static sf::String pentomino[16];
    static sf::String tetromino[7];

    int OFFSET_X;
    int OFFSET_Y;

    int COUNT_OF_PIECES;
    int nFieldWidth;
    int nFieldHeight;
    int COUNT_OF_BLOCKS;

    unsigned char *pField;
    sf::String getElementOfPiece(int x, int y);

    unsigned char* field() const;
    int rotate(int px, int py, int r);
    bool doesPieceFit(int nTetronimo, int nRotation, int nPosX, int nPosY);
    constexpr static const int GRID_SIZE = 32;

    const sf::Vector2i RESOLUTION;

    constexpr static const int ANIM_BLOCK = 17;
    constexpr static const int BOUNDARY_BLOCK = 18;
    void initBoard(int level);
    void setPentomino();
    void setTetromino();
};

#endif // GAME_H
