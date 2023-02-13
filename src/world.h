#ifndef WORLD_H
#define WORLD_H
#include "utils/resource_holder.h"
#include "utils/resource_identifiers.h"
#include "SFX/sound_player.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "game.h"

#include <array>
#include <queue>


// Forward declaration
namespace sf
{
    class RenderTarget;
    class Event;
}

class World : private sf::NonCopyable
{
    public:
                                            World(sf::RenderWindow& outputTarget, FontHolder& fonts, SoundPlayer& sounds);
        void								update(sf::Time dt);
        void								draw();

        void processInput(const sf::Event& event);


        bool 								hasAlivePlayer() const;
        bool 								hasPlayerReachedEnd() const;


    private:
        void								loadTextures();
        void								adaptPlayerPosition();
        void								adaptPlayerVelocity();
        void								handleCollisions();
        void								updateSounds();

        void								buildScene();
        void								spawnEnemies();
        void								destroyEntitiesOutsideView();
        void								guideMissiles();
        sf::FloatRect						getViewBounds() const;
        sf::FloatRect						getBattlefieldBounds() const;


    private:
        enum Layer
        {
            Background,
            LowerAir,
            UpperAir,
            LayerCount
        };


    private:
        sf::RenderWindow&					mTarget;
        sf::View							mWorldView;
        TextureHolder						mTextures;
        FontHolder&							mFonts;
        SoundPlayer&						mSounds;


        sf::FloatRect						mWorldBounds;



        void render();
        void drawField();
        void drawCurrentPiece();
        void drawNextPiece();
        void drawScore();
        void drawGameOverText();
        void handlePlayerInput();

        Game mGame;
        bool bMoveLeft, bMoveRight, bMoveDown, bRotate;
        int nCurrentPiece = 0;
        int nNextPiece = 0;
        int nCurrentRotation = 0;
        int nCurrentX = Game::nFieldWidth / 2;
        int nCurrentY = 0;
        int nSpeed = 20;
        int nSpeedCount = 0;
        bool bForceDown = false;
        bool bRotateHold = true;
        int nPieceCount = 0;
        int nScore = 0;
        std::vector<int> vLines;
        bool bGameOver = false;
        bool isGenerateNewPiece = false;
};
#endif // WORLD_H
