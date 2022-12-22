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

// MARK: - Private:

Game::Game()
{
    _playerHealth = 0;
}

void Game::reset()
{
    _playerHealth = 3;
}
