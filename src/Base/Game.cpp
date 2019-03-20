#include "Base/Game.hpp"

#include <SFML/System.hpp>
#include "States/OrangeState/OrangeState.hpp"

using PopHead::Base::Game;

Game::Game()
        : mGameData {}
        , mSoundPlayer { new Audio::SoundPlayer() }
        , mMusicPlayer { new Audio::MusicPlayer() }
        , mTextures { new Resources::TextureHolder() }
        , mFonts { new Resources::FontHolder() }
        , mShaders { new Resources::ShaderHolder() }
        , mStateMachine { new States::StateMachine() }
        , mInput { new Input::Input() }
        , mRenderer { new Renderer::Renderer() }
{
    mGameData.reset( new GameData(
            mSoundPlayer.get(),
            mMusicPlayer.get(),
            mTextures.get(),
            mFonts.get(),
            mShaders.get(),
            mStateMachine.get(),
            mInput.get(),
            mRenderer.get() ) );
    run();
}

void Game::run()
{
    sf::Clock clock;
    const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(true)///in the future here will be something like mRenderer->isWindowOpen()
    {
        ///mStateMachine->changingStatesProcess();
        ///mStateMachine->input();
        timeSinceLastUpdate += clock.restart();

        while(timeSinceLastUpdate > timePerFrame){
            timeSinceLastUpdate -= timePerFrame;
            ///mStateMachine->update(timePerFrame);
            mRenderer->draw();
        }
    }
}

void Game::input()
{

}

void Game::update( float delta )
{

}

void Game::draw()
{

}
