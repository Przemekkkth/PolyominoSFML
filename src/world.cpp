#include "world.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Sleep.hpp>
#include <algorithm>
#include <cmath>
#include <limits>
#include "states/game_state.h"


World::World(sf::RenderWindow& outputTarget, FontHolder& fonts, SoundPlayer& sounds)
    : mTarget(outputTarget)
    , mTextures()
    , mFonts(fonts)
    , mSounds(sounds)

{
    mGame.initBoard(GameState::choosenLevel);
    loadTextures();
    srand(time(0));
    nCurrentX = mGame.FIELD_WIDTH / 2;
    nCurrentY = 0;
    nCurrentRotation = 0;
    nCurrentPiece = rand() % mGame.COUNT_OF_PIECES;
    nNextPiece = rand() % mGame.COUNT_OF_PIECES;
    bMoveLeft = bMoveRight = bRotate = false;
    isGenerateNewPiece = true;
}

void World::update(sf::Time)
{
    if(!bGameOver)
    {
        handlePlayerInput();
        nSpeedCount++;
        bForceDown = (nSpeedCount == nSpeed);
        // Handle player movement

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


            // Test if piece can be moved down
            if (mGame.doesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
            {
                nCurrentY++; // It can, so do it!
            }
            else
            {
                // It can't! Lock the piece in place
                for (int px = 0; px < mGame.COUNT_OF_BLOCKS; px++)
                {
                    for (int py = 0; py < mGame.COUNT_OF_BLOCKS; py++)
                    {
                        if(mGame.getElementOfPiece(nCurrentPiece, mGame.rotate(px, py, nCurrentRotation)) != '.')
                        {
                            mGame.field()[(nCurrentY + py) * mGame.FIELD_WIDTH + (nCurrentX + px)] = nCurrentPiece+1;
                        }

                    }

                }

                // Check for lines
                for (int py = 0; py < mGame.COUNT_OF_BLOCKS; py++)
                {
                    if(nCurrentY + py < mGame.FIELD_HEIGHT - 1)
                    {
                        bool bLine = true;
                        for (int px = 1; px < mGame.FIELD_WIDTH - 1; px++)
                        {
                            bLine &= (mGame.field()[(nCurrentY + py) * mGame.FIELD_WIDTH + px]) != 0;
                        }


                        if (bLine)
                        {
                            // Remove Line, set to =
                            for (int px = 1; px < mGame.FIELD_WIDTH - 1; px++)
                            {
                                mGame.field()[(nCurrentY + py) * mGame.FIELD_WIDTH + px] = Polyomino::ANIM_BLOCK;
                            }

                            mTarget.clear();
                            drawField();
                            mTarget.display();
                            sf::sleep(sf::milliseconds(50));
                            mSounds.play(SoundEffect::FilledRow);


                            vLines.push_back(nCurrentY + py);
                        }
                    }
                }



                nScore += 25;


                if(!vLines.empty())	nScore += (1 << vLines.size()) * 100;

                isGenerateNewPiece = true;



            }

        }

    }
    bMoveLeft = bMoveRight = bRotate = false;

    if (!vLines.empty())
    {
        for (auto &v : vLines)
            for (int px = 1; px < mGame.FIELD_WIDTH - 1; px++)
            {
                for (int py = v; py > 0; py--)
                    mGame.field()[py * mGame.FIELD_WIDTH + px] = mGame.field()[(py - 1) * mGame.FIELD_WIDTH + px];
                mGame.field()[px] = 0;
            }

        vLines.clear();
    }


    if(isGenerateNewPiece)
    {
        isGenerateNewPiece = false;
        bMoveDown = false;
        mTarget.setKeyRepeatEnabled(false);
        nCurrentX = mGame.FIELD_WIDTH / 2;
        nCurrentY = 0;
        nCurrentPiece = nNextPiece;
        nNextPiece = rand() % mGame.COUNT_OF_PIECES;

        bGameOver = !mGame.doesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
    }

}

void World::draw()
{
    render();
}

void World::processInput(const sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Left)
        {
            mTarget.setKeyRepeatEnabled(false);
            bMoveLeft = true;
        }
        if(event.key.code == sf::Keyboard::Right)
        {
            mTarget.setKeyRepeatEnabled(false);
            bMoveRight = true;
        }
        if(event.key.code == sf::Keyboard::Down)
        {
            mTarget.setKeyRepeatEnabled(true);
            bMoveDown = true;
        }
        if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Z)
        {
            mTarget.setKeyRepeatEnabled(false);
            bRotate = true;
        }
    }
    if(event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == sf::Keyboard::Left)
        {
            bMoveLeft = false;
        }
        if(event.key.code == sf::Keyboard::Right)
        {
            bMoveRight = false;
        }
        if(event.key.code == sf::Keyboard::Down)
        {
            bMoveDown = false;
        }
        if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Z)
        {
            bRotate = false;
        }
        if(event.key.code == sf::Keyboard::R)
        {
            if(bGameOver)
            {
                bGameOver = false;
                mGame.initBoard(GameState::choosenLevel);
                nScore = 0;
            }
        }

    }

}

bool World::isGameOver() const
{
    return bGameOver;
}

void World::loadTextures()
{
    mTextures.load(Textures::Blocks, "res/blocks.png");
}

void World::render()
{
    drawField();
    drawCurrentPiece();
    drawNextPiece();
    drawScore();
}

void World::drawField()
{
    for (int x = 0; x < mGame.FIELD_WIDTH; x++)
    {
        for (int y = 0; y < mGame.FIELD_HEIGHT; y++)
        {
            sf::Sprite sprite;
            sprite.setTexture(mTextures.get(Textures::Blocks));
            sprite.setTextureRect(sf::IntRect(int(mGame.pField[y*mGame.FIELD_WIDTH + x])*Polyomino::GRID_SIZE, 0, Polyomino::GRID_SIZE, Polyomino::GRID_SIZE));
            sprite.setPosition(x*Polyomino::GRID_SIZE + mGame.OFFSET_X/2, y*Polyomino::GRID_SIZE + mGame.OFFSET_Y);
            mTarget.draw(sprite);
        }
    }
}

void World::drawCurrentPiece()
{

    for (int px = 0; px < mGame.COUNT_OF_BLOCKS; px++)
    {
        for (int py = 0; py < mGame.COUNT_OF_BLOCKS; py++)
        {
            if(mGame.getElementOfPiece(nCurrentPiece, mGame.rotate(px, py, nCurrentRotation))  != '.')
            {
                sf::Sprite sprite;
                sprite.setTexture(mTextures.get(Textures::Blocks));
                sprite.setTextureRect(sf::IntRect((nCurrentPiece+1)*Polyomino::GRID_SIZE, 0, Polyomino::GRID_SIZE, Polyomino::GRID_SIZE));
                sprite.setPosition((nCurrentX + px)*Polyomino::GRID_SIZE + mGame.OFFSET_X/2 , (nCurrentY + py)*Polyomino::GRID_SIZE + mGame.OFFSET_Y);
                mTarget.draw(sprite);
            }

        }
    }
}

void World::drawNextPiece()
{
    sf::Text nextText;
    nextText.setFont(mFonts.get(Fonts::ID::Main));
    nextText.setCharacterSize(20);
    nextText.setFillColor(sf::Color::White);
    nextText.setPosition(mGame.RESOLUTION.x - (mGame.COUNT_OF_BLOCKS-1)*Polyomino::GRID_SIZE, mGame.OFFSET_Y+75);
    nextText.setStyle(sf::Text::Bold);
    nextText.setString("Next: ");
    mTarget.draw(nextText);


    for (int px = 0; px < mGame.COUNT_OF_BLOCKS; px++)
    {
        for (int py = 0; py < mGame.COUNT_OF_BLOCKS; py++)
        {
            if( mGame.getElementOfPiece(nNextPiece, mGame.rotate(px, py, 0)) != '.' )
            {
                sf::Sprite sprite;
                sprite.setTexture(mTextures.get(Textures::Blocks));
                sprite.setTextureRect(sf::IntRect((nNextPiece+1)*Polyomino::GRID_SIZE, 0, Polyomino::GRID_SIZE, Polyomino::GRID_SIZE));
                sprite.setPosition(px*Polyomino::GRID_SIZE + mGame.RESOLUTION.x - (mGame.COUNT_OF_BLOCKS+1)*Polyomino::GRID_SIZE, (py)*Polyomino::GRID_SIZE + mGame.OFFSET_Y+100);
                mTarget.draw(sprite);
            }

        }
    }

}

void World::drawScore()
{
    sf::Text text;
    text.setFont(mFonts.get(Fonts::ID::Main));
    text.setFillColor(sf::Color::White);
    text.setString(sf::String(std::string("Score: ") + std::to_string(nScore)));
    text.setPosition(mGame.RESOLUTION.x-text.getLocalBounds().width, 0);
    mTarget.draw(text);
}

void World::handlePlayerInput()
{
    if(bMoveLeft)
    {
        if(mGame.doesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY))
        {
            nCurrentX--;
        }
    }
    else if(bMoveRight)
    {
        if(mGame.doesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY))
        {
            nCurrentX++;
        }
    }
    else if(bMoveDown)
    {
        if(mGame.doesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
        {
            nCurrentY++;
        }
    }
    else if(bRotate)
    {
        if(mGame.doesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY))
        {
            nCurrentRotation++;
        }
        bRotate = false;
    }
}
