//
//  SpriteLoader.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#include "SpriteLoader.h"

USING_NS_AX;

const std::string BACKGROUND = "sprites/background-1.png";

Sprite* SpriteLoader::createBackground()
{
    auto sprite = Sprite::create(BACKGROUND);
    if (sprite == nullptr) {
        log("Error creating BG sprite");
        return nullptr;
    }
    sprite->getTexture()->setAliasTexParameters();
    sprite->setScale(2, 2);
    return sprite;
}

Sprite* SpriteLoader::createRock()
{
    auto sprite = Sprite::create("sprites/rock-big.png");
    if (sprite == nullptr) {
        log("Error creating rock sprite");
        return nullptr;
    }
    sprite->getTexture()->setAliasTexParameters();
    sprite->setScale(2, 2);
    return sprite;
}

// Workaround to avoid sprite sheets for now
Sprite* SpriteLoader::createCoinAnimation()
{
    auto sprite = Sprite::create("sprites/coin/gold_coin-0.png");
    sprite->getTexture()->setAliasTexParameters();
    sprite->setScale(2, 2);
    
    auto animation = Animation::create();
    for (int i = 0; i < 8; i++) {
        char fileName[64] = {0};
        sprintf(fileName, "sprites/coin/gold_coin-%d.png", i);
        animation->addSpriteFrameWithFile(fileName);
    }
    
    auto frames = animation->getFrames();
    for (auto& frame : frames) {
        frame->getSpriteFrame()->getTexture()->setAliasTexParameters();
    }
    
    animation->setLoops(-1);
    animation->setDelayPerUnit(0.07);
    animation->setRestoreOriginalFrame(false);
    
    auto animate = Animate::create(animation);
    sprite->runAction(animate);
    
    return sprite;
}
