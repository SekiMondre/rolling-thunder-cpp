//
//  DebugCollisionScene.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#include "DebugCollisionScene.h"

USING_NS_AX;

DebugCollisionScene::DebugCollisionScene()
{
    // Constructor
}

DebugCollisionScene::~DebugCollisionScene()
{
    // Destructor
}

bool DebugCollisionScene::init()
{
    if (!Scene::init()) return false;
    return true;
}