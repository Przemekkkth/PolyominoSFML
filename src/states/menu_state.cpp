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

    sf::Texture& ptexture = context.textures->get(Textures::PolyominoString);
    mTitleStringSprite.setTexture(ptexture);
    mTitleStringSprite.setPosition(30, 30);

    auto monominoButton = std::make_shared<GUI::Button>(context);
    monominoButton->setPosition(230, 200);
    monominoButton->setText("Monomino");
    monominoButton->setCallback([this] ()
    {
        GameState::choosenLevel = 1;
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto dominoButton = std::make_shared<GUI::Button>(context);
    dominoButton->setPosition(230, 275);
    dominoButton->setText("Domino");
    dominoButton->setCallback([this] ()
    {
        GameState::choosenLevel = 2;
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto triominoButton = std::make_shared<GUI::Button>(context);
    triominoButton->setPosition(230, 350);
    triominoButton->setText("Triomino");
    triominoButton->setCallback([this] ()
    {
        GameState::choosenLevel = 3;
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto tetrominoButton = std::make_shared<GUI::Button>(context);
    tetrominoButton->setPosition(230, 425);
    tetrominoButton->setText("Tetromino");
    tetrominoButton->setCallback([this] ()
    {
        GameState::choosenLevel = 4;
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto pentominoButton = std::make_shared<GUI::Button>(context);
    pentominoButton->setPosition(230, 500);
    pentominoButton->setText("Pentomino");
    pentominoButton->setCallback([this] ()
    {
        GameState::choosenLevel = 5;
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto exitButton = std::make_shared<GUI::Button>(context);
    exitButton->setPosition(230, 575);
    exitButton->setText("Exit");
    exitButton->setCallback([this] ()
    {
        requestStackPop();
    });

    mGUIContainer.pack(monominoButton);
    mGUIContainer.pack(dominoButton);
    mGUIContainer.pack(triominoButton);
    mGUIContainer.pack(tetrominoButton);
    mGUIContainer.pack(pentominoButton);
    //mGUIContainer.pack(settingsButton);
    mGUIContainer.pack(exitButton);

    // Play menu theme
    //context.music->play(Music::MenuTheme);
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    //window.draw(mBackgroundSprite);
    window.draw(mTitleStringSprite);
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
