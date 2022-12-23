//
//  DebugAnimationScene.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 13/12/22.
//

#include "DebugAnimationScene.h"
#include "Debug.h"
#include "RollingThunder.h"

USING_NS_AX;

//setName("Debug");
//std::string name{getName()};
//log("Scene init: %s", name.c_str());

DebugAnimationScene::DebugAnimationScene()
{}

DebugAnimationScene::~DebugAnimationScene()
{
    log("[DEBUG] Destroying: Animation Test");
}

bool DebugAnimationScene::init()
{
    if (!Scene::init()) return false;
    log("[DEBUG] Init scene: Animation Test");
    
    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    auto winSize = _director->getWinSize();
    
    auto root = Node::create();
    root->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, origin.y));
    addChild(root);
    
    auto bg = SpriteLoader::load(ImageAsset::BACKGROUND);
    bg->setAnchorPoint(Vec2(0.5, 0));
    root->addChild(bg);
    
    for (int i = 0; i < 3; i++)
    {
        auto rock = SpriteLoader::load(ImageAsset::ROCK_BIG);
        rock->setPosition(Vec2(152 * (i - 1), visibleSize.height - 76));
        root->addChild(rock);
    }
    
    auto enemy1 = SpriteAnimation::createEnemyNormal();
    enemy1->setPosition(Vec2(-152 - 16, visibleSize.height - 152 - 76));
    root->addChild(enemy1);
    
    auto enemy2 = SpriteAnimation::createEnemyBig();
    enemy2->setPosition(Vec2(0, visibleSize.height - 152 - 76));
    root->addChild(enemy2);
    
    auto enemy3 = SpriteAnimation::createEnemyDodger();
    enemy3->setPosition(Vec2(152 + 16, visibleSize.height - 152 - 76));
    root->addChild(enemy3);
    
    for (int i = 0; i < 5; i++)
    {
        auto coin = SpriteAnimation::createGoldCoin();
        coin->setPosition(Vec2(76 * (i - 2), visibleSize.height * 0.65));
        root->addChild(coin);
    }
    
    for (int i = 0; i < 3; i++)
    {
        int idx = i + 1;
        float h = visibleSize.height * (0.57 - 0.10 * i);
        
        auto playerIdle = Sprite::create();
        playerIdle->setScale(2.0f, 2.0f);
        playerIdle->runAction(Animate::create(SpriteAnimation::loadPlayerIdleAnimation(idx)));
        playerIdle->setPosition(Vec2(-140, h));
        root->addChild(playerIdle);
        
        auto playerRoll = Sprite::create();
        playerRoll->setScale(2.0f, 2.0f);
        playerRoll->runAction(Animate::create(SpriteAnimation::loadPlayerRollAnimation(idx)));
        playerRoll->setPosition(Vec2(0, h));
        root->addChild(playerRoll);
        
        auto playerDead = Sprite::create();
        playerDead->setScale(2.0f, 2.0f);
        playerDead->runAction(Animate::create(SpriteAnimation::loadPlayerDeadAnimation(idx)));
        playerDead->setPosition(Vec2(140, h));
        root->addChild(playerDead);
    }
    
    auto powerup = SpriteAnimation::createCrackle();
    powerup->setPosition(Vec2(0, visibleSize.height * 0.10));
    root->addChild(powerup);
    
    auto exitButton = Debug::createExitButton(AX_CALLBACK_0(DebugAnimationScene::exitScene, this));
    
    auto playButton = Debug::createColorButton("P", 32, Vec2(64, 64), Color4B::BLUE);
    playButton->setCallback(AX_CALLBACK_0(DebugAnimationScene::animateOnce, this));
    playButton->setPosition(Vec2(visibleSize.width * 0.5 - 32 - 16, -visibleSize.height * 0.5 + 32 + 16));
    
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(exitButton);
    menuItems.pushBack(playButton);
    auto menu = Menu::createWithArray(menuItems);
    this->addChild(menu);
    
    return true;
}

void DebugAnimationScene::animateOnce() {
    auto sprite = SpriteAnimation::createEphemeralSmokeHit();
    sprite->setPosition(Vec2(300, 140));
    addChild(sprite);
}

void DebugAnimationScene::exitScene()
{
    _director->replaceScene(DebugMenuScene::create());
}
