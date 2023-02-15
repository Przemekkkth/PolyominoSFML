#include "menu_state.h"

#include "../GUI/button.h"
//#include "../utils/utility.h"
#include "../utils/resource_holder.h"
#include "../SFX/music_player.h"
#include "game_state.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context)
    , mGUIContainer()
{
    sf::Texture& texture = context.textures->get(Textures::TitleScreen);
    mBackgroundSprite.setTexture(texture);

    auto playButton0 = std::make_shared<GUI::Button>(context);
    playButton0->setPosition(20, 100);
    playButton0->setText("Tetromino");
    playButton0->setCallback([this] ()
    {
        GameState::choosenLevel = 4;
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto playButton1 = std::make_shared<GUI::Button>(context);
    playButton1->setPosition(20, 200);
    playButton1->setText("Pentomino");
    playButton1->setCallback([this] ()
    {
        GameState::choosenLevel = 5;
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto playButton2 = std::make_shared<GUI::Button>(context);
    playButton2->setPosition(400, 200);
    playButton2->setText("Triomino");
    playButton2->setCallback([this] ()
    {
        GameState::choosenLevel = 3;
        requestStackPop();
        requestStackPush(States::Game);
    });


    auto exitButton = std::make_shared<GUI::Button>(context);
    exitButton->setPosition(100, 400);
    exitButton->setText("Exit");
    exitButton->setCallback([this] ()
    {
        requestStackPop();
    });

    mGUIContainer.pack(playButton0);
    mGUIContainer.pack(playButton1);
    mGUIContainer.pack(playButton2);
    //mGUIContainer.pack(settingsButton);
    mGUIContainer.pack(exitButton);

    // Play menu theme
    //context.music->play(Music::MenuTheme);
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    mGUIContainer.handleEvent(event);
    return false;
}
