#include "game_state.h"
#include "../SFX/music_player.h"
#include <SFML/Graphics/RenderWindow.hpp>

int GameState::choosenLevel = 4;
GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window, *context.fonts, *context.sounds)
, mPlayer(*context.player)
{

}

void GameState::draw()
{
    mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
    mWorld.update(dt);
    if(mWorld.isGameOver())
    {
        requestStackPush(States::GameOver);
    }
    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{

    // Escape pressed, trigger the pause screen
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStackPush(States::Pause);

    mWorld.processInput(event);
    return true;
}
