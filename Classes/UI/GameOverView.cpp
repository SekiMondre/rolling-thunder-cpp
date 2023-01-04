//
//  GameOverView.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 04/01/23.
//

#include "GameOverView.h"
#include "RollingThunder.h"

USING_NS_AX;

GameOverView::GameOverView()
{
    // Constructor
}

GameOverView::~GameOverView()
{
    // Destructor
}

bool GameOverView::init()
{
    if (!Node::init()) return false;
    return true;
}
