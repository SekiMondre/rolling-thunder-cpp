//
//  Subsystems.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 23/12/22.
//

#include "Subsystems.h"
#include "RollingThunder.h"

USING_NS_AX;

void Subsystems::startGameSystems()
{
    auto spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile("sprites/ht-sprites.plist");
    spriteCache->addSpriteFramesWithFile("sprites/ui-sprites.plist");
    
    SpriteLoader::start();
    RNG::start();
}
