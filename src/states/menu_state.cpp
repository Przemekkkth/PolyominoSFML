#include "menu_state.h"

#include "../GUI/button.h"
#include "../utils/resource_holder.h"
#include "../SFX/music_player.h"
#include "../application.h"
#include "game_state.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context)
    , mGUIContainer()
{
    sf::Texture& texture = context.textures->get(Textures::PolyominoString);
    mTitleStringSprite.setTexture(texture);
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

    auto musicButton = std::make_shared<GUI::Button>(context);
    musicButton->setPosition(20, 575);
    musicButton->setText("Music");
    musicButton->setCallback([this, musicButton](){
        Application::IS_PLAY_MUSIC = !Application::IS_PLAY_MUSIC;
        if(Application::IS_PLAY_MUSIC)
        {
            getContext().music->play(Music::MenuTheme);
            musicButton->setTextColor(sf::Color::White);
            musicButton->setText("Music", sf::Text::Regular);
        }
        else
        {
            getContext().music->stop();
            musicButton->setTextColor(sf::Color::Red);
            musicButton->setText("Music", sf::Text::StrikeThrough);
        }
    });
    if(!Application::IS_PLAY_MUSIC)
    {
        musicButton->setTextColor(sf::Color::Red);
        musicButton->setText("Music", sf::Text::StrikeThrough);
    }

    auto soundButton = std::make_shared<GUI::Button>(context);
    soundButton->setPosition(230, 575);
    soundButton->setText("Sound");
    soundButton->setCallback([soundButton] ()
    {
        Application::IS_PLAY_SOUND = !Application::IS_PLAY_SOUND;
        if(Application::IS_PLAY_SOUND)
        {
            soundButton->setTextColor(sf::Color::White);
            soundButton->setText("Sound", sf::Text::Regular);
        }
        else
        {
            soundButton->setTextColor(sf::Color::Red);
            soundButton->setText("Sound", sf::Text::StrikeThrough);
        }
    });
    if(!Application::IS_PLAY_SOUND)
    {
        soundButton->setTextColor(sf::Color::Red);
        soundButton->setText("Sound", sf::Text::StrikeThrough);
    }


    auto exitButton = std::make_shared<GUI::Button>(context);
    exitButton->setPosition(440, 575);
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
    mGUIContainer.pack(musicButton);
    mGUIContainer.pack(soundButton);
    mGUIContainer.pack(exitButton);

    // Play music theme
    if(Application::IS_PLAY_MUSIC)
    {
       context.music->play(Music::MenuTheme);
    }
    else
    {
        context.music->stop();
    }
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

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
