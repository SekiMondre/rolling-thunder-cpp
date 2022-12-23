//
//  Game.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 21/12/22.
//

#include "Game.h"

USING_NS_AX;

static Game* _sharedInstance = nullptr;

// MARK: - Public:

Game* Game::getInstance()
{
    if (!_sharedInstance) {
        _sharedInstance = new Game;
    }
    return _sharedInstance;
}

Vec2 Game::getSceneSize()
{
    return Director::getInstance()->getWinSize();
}

float Game::getSceneWidth()
{
    return Director::getInstance()->getWinSize().width;
}

float Game::getSceneHeight()
{
    return Director::getInstance()->getWinSize().height;
}

void Game::reset()
{
    _state = IDLE;
    _playerHealth = 3;
}

GameState Game::getState()
{
    return _state;
}

void Game::setState(GameState state)
{
    _state = state;
}

float Game::getScrollingSpeed()
{
    return _scrollingSpeed;
}

void Game::setScrollingSpeed(float speed)
{
    _scrollingSpeed = speed;
}

// MARK: - Private:

Game::Game()
    : _state(IDLE)
    , _playerHealth(0)
    , _scrollingSpeed(0.0f)
{}
