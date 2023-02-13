#ifndef GAME_H
#define GAME_H
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Game
{
public:
    Game();
    static sf::String pentomino[16];

    constexpr static int OFFSET_X = 100;
    constexpr static int OFFSET_Y = 50;
    constexpr static int nScreenWidth = 80;
    constexpr static int nScreenHeighht = 30;

    constexpr static const int COUNT_OF_PIECES = 16;
    constexpr static int nFieldWidth = 13;
    constexpr static int nFieldHeight = 19;
    constexpr static const int COUNT_OF_BLOCKS = 5;
    unsigned char *pField;


    unsigned char* field() const;
    int rotate(int px, int py, int r);
    bool doesPieceFit(int nTetronimo, int nRotation, int nPosX, int nPosY);
    constexpr static const int GRID_SIZE = 32;

    const sf::Vector2i RESOLUTION;

    constexpr static const int ANIM_BLOCK = 17;
    constexpr static const int BOUNDARY_BLOCK = 18;
    void initBoard();
};

#endif // GAME_H
