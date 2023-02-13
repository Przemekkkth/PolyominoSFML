#include "world.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <cmath>
#include <limits>



World::World(sf::RenderWindow& outputTarget, FontHolder& fonts, SoundPlayer& sounds)
    : mTarget(outputTarget)
    , mWorldView(outputTarget.getDefaultView())
    , mTextures()
    , mFonts(fonts)
    , mSounds(sounds)

{
    loadTextures();
    buildScene();
    srand(time(0));
    nCurrentX = Game::nFieldWidth / 2;
    nCurrentY = 0;
    nCurrentRotation = 0;
    nCurrentPiece = rand() % Game::COUNT_OF_PIECES;
    nNextPiece = rand() % Game::COUNT_OF_PIECES;
    bMoveLeft = bMoveRight = bRotate = false;
    isGenerateNewPiece = true;
}

void World::update(sf::Time dt)
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
                for (int px = 0; px < Game::COUNT_OF_BLOCKS; px++)
                {
                    for (int py = 0; py < Game::COUNT_OF_BLOCKS; py++)
                    {
                        if (mGame.pentomino[nCurrentPiece][mGame.rotate(px, py, nCurrentRotation)] != '.')
                        {
                            mGame.field()[(nCurrentY + py) * Game::nFieldWidth + (nCurrentX + px)] = nCurrentPiece+1;
                        }

                    }

                }

                // Check for lines
                for (int py = 0; py < Game::COUNT_OF_BLOCKS; py++)
                {
                    if(nCurrentY + py < Game::nFieldHeight - 1)
                    {
                        bool bLine = true;
                        for (int px = 1; px < Game::nFieldWidth - 1; px++)
                        {
                            bLine &= (mGame.field()[(nCurrentY + py) * Game::nFieldWidth + px]) != 0;
                        }


                        if (bLine)
                        {
                            // Remove Line, set to =
                            for (int px = 1; px < Game::nFieldWidth - 1; px++)
                            {
                                mGame.field()[(nCurrentY + py) * Game::nFieldWidth + px] = Game::ANIM_BLOCK;
                            }

    //                        mTarget.clear();
    //                        drawField();
    //                        mWindow.display();
    //                        sf::sleep(sf::milliseconds(350));


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
            for (int px = 1; px < Game::nFieldWidth - 1; px++)
            {
                for (int py = v; py > 0; py--)
                    mGame.field()[py * Game::nFieldWidth + px] = mGame.field()[(py - 1) * Game::nFieldWidth + px];
                mGame.field()[px] = 0;
            }

        vLines.clear();
    }


    if(isGenerateNewPiece)
    {
        isGenerateNewPiece = false;
        bMoveDown = false;
        mTarget.setKeyRepeatEnabled(false);
        nCurrentX = Game::nFieldWidth / 2;
        nCurrentY = 0;
        nCurrentPiece = nNextPiece;
        nNextPiece = rand() % Game::COUNT_OF_PIECES;

        bGameOver = !mGame.doesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
    }

    //updateSounds();
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
                mGame.initBoard();
                nScore = 0;
            }
        }

    }

}

void World::loadTextures()
{
    mTextures.load(Textures::Entities, "Media/Textures/Entities.png");
    mTextures.load(Textures::Jungle, "Media/Textures/Jungle.png");
    mTextures.load(Textures::Explosion, "Media/Textures/Explosion.png");
    mTextures.load(Textures::Particle, "Media/Textures/Particle.png");
    mTextures.load(Textures::FinishLine, "Media/Textures/FinishLine.png");
    mTextures.load(Textures::Blocks, "res/blocks.png");
}


void World::updateSounds()
{
    mSounds.setListenerPosition(sf::Vector2f(0,0));
    mSounds.removeStoppedSounds();
}

void World::buildScene()
{

}




void World::render()
{
    drawField();
    drawCurrentPiece();
    drawNextPiece();
    drawScore();
    if(bGameOver)
    {
        drawGameOverText();
    }
}

void World::drawField()
{
    for (int x = 0; x < Game::nFieldWidth; x++)
    {
        for (int y = 0; y < Game::nFieldHeight; y++)
        {
            sf::Sprite sprite;
            sprite.setTexture(mTextures.get(Textures::Blocks));
            sprite.setTextureRect(sf::IntRect(int(mGame.pField[y*Game::nFieldWidth + x])*Game::GRID_SIZE, 0, Game::GRID_SIZE, Game::GRID_SIZE));
            sprite.setPosition(x*Game::GRID_SIZE + Game::OFFSET_X/2, y*Game::GRID_SIZE + Game::OFFSET_Y);
            mTarget.draw(sprite);
        }
    }
}

void World::drawCurrentPiece()
{

    for (int px = 0; px < Game::COUNT_OF_BLOCKS; px++)
    {
        for (int py = 0; py < Game::COUNT_OF_BLOCKS; py++)
        {
            if (mGame.pentomino[nCurrentPiece][mGame.rotate(px, py, nCurrentRotation)] != '.')
            {
                sf::Sprite sprite;
                sprite.setTexture(mTextures.get(Textures::Blocks));
                sprite.setTextureRect(sf::IntRect((nCurrentPiece+1)*Game::GRID_SIZE, 0, Game::GRID_SIZE, Game::GRID_SIZE));
                sprite.setPosition((nCurrentX + px)*Game::GRID_SIZE + Game::OFFSET_X/2 , (nCurrentY + py)*Game::GRID_SIZE + Game::OFFSET_Y);
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
    nextText.setPosition(mGame.RESOLUTION.x - (Game::COUNT_OF_BLOCKS-1)*Game::GRID_SIZE, Game::OFFSET_Y+75);
    nextText.setStyle(sf::Text::Bold);
    nextText.setString("Next: ");
    mTarget.draw(nextText);


    for (int px = 0; px < Game::COUNT_OF_BLOCKS; px++)
    {
        for (int py = 0; py < Game::COUNT_OF_BLOCKS; py++)
        {
            if (mGame.pentomino[nNextPiece][mGame.rotate(px, py, 0)] != '.')
            {
                sf::Sprite sprite;
                sprite.setTexture(mTextures.get(Textures::Blocks));
                sprite.setTextureRect(sf::IntRect((nNextPiece+1)*Game::GRID_SIZE, 0, Game::GRID_SIZE, Game::GRID_SIZE));
                sprite.setPosition(px*Game::GRID_SIZE + mGame.RESOLUTION.x - (Game::COUNT_OF_BLOCKS+1)*Game::GRID_SIZE, (py)*Game::GRID_SIZE + Game::OFFSET_Y+100);
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

void World::drawGameOverText()
{
    sf::Text text;
    text.setFont(mFonts.get(Fonts::ID::Main));
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    text.setString("Game Over");
    text.setCharacterSize(100);
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(mGame.RESOLUTION.x/2, mGame.RESOLUTION.y/2);

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
