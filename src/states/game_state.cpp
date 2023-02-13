#include "game_state.h"
#include "../SFX/music_player.h"
#include <SFML/Graphics/RenderWindow.hpp>

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window, *context.fonts, *context.sounds)
, mPlayer(*context.player)
{
    mPlayer.setMissionStatus(Player::MissionRunning);
    // Play game theme
    //context.music->play(Music::MissionTheme);
}

void GameState::draw()
{
    mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
    mWorld.update(dt);
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
