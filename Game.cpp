//
//  Game.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 21/12/22.
//

#include "Game.h"

static Game* _sharedInstance = nullptr;

Game* Game::getInstance()
{
    if (!_sharedInstance) {
        _sharedInstance = new Game;
    }
    return _sharedInstance;
}

Game::Game()
{
    _playerHealth = 0;
}

void Game::reset()
{
    _playerHealth = 3;
}
