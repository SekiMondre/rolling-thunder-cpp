//
//  DebugAnimationScene.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 13/12/22.
//

#include "DebugAnimationScene.h"
#include "Debug.h"

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
    
    auto bg = SpriteLoader::load(BACKGROUND);
    bg->setAnchorPoint(Vec2(0.5, 0));
    root->addChild(bg);
    
    for (int i = 0; i < 3; i++)
    {
        auto rock = SpriteLoader::load(ROCK_BIG);
        rock->setPosition(Vec2(152 * (i - 1), visibleSize.height - 76));
        root->addChild(rock);
    }
    
    auto enemy1 = SpriteLoader::loadAnimated(ENEMY_COMMON, 8);
    enemy1->setPosition(Vec2(-152 - 16, visibleSize.height - 152 - 76));
    root->addChild(enemy1);
    
    auto enemy2 = SpriteLoader::loadAnimated(ENEMY_BIG, 8);
    enemy2->setPosition(Vec2(0, visibleSize.height - 152 - 76));
    root->addChild(enemy2);
    
    auto enemy3 = SpriteLoader::loadAnimatedEnemy3();
    enemy3->setPosition(Vec2(152 + 16, visibleSize.height - 152 - 76));
    root->addChild(enemy3);
    
    for (int i = 0; i < 5; i++)
    {
        auto coin = SpriteLoader::loadAnimated(GOLD_COIN, 8);
        coin->setPosition(Vec2(76 * (i - 2), visibleSize.height * 0.65));
        root->addChild(coin);
    }
    
    auto playerIdle = SpriteLoader::loadPlayerIdle();
    playerIdle->setPosition(Vec2(-152, visibleSize.height * 0.55));
    root->addChild(playerIdle);
    
    auto playerRoll = SpriteLoader::loadAnimated("tatu-1-ball", 3);
    playerRoll->setPosition(Vec2(0, visibleSize.height * 0.55));
    root->addChild(playerRoll);
    
    auto playerDead = SpriteLoader::loadPlayerDead();
    playerDead->setPosition(Vec2(152, visibleSize.height * 0.55));
    root->addChild(playerDead);
    
    auto powerup = SpriteLoader::loadAnimatedCrackle();
    powerup->setPosition(Vec2(0, visibleSize.height * 0.40));
    root->addChild(powerup);
    
    auto r1 = SpriteLoader::load(ROCK_MEDIUM);
    r1->setPosition(Vec2(-150, 300));
    root->addChild(r1);
    
    auto r2 = SpriteLoader::load(ROCK_SMALL);
    r2->setPosition(Vec2(-150, 100));
    root->addChild(r2);
    
    auto b = SpriteLoader::load(GOLD_BAR_3X);
    b->setPosition(Vec2(0, 200));
    root->addChild(b);
    
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
    auto frames = SpriteLoader::loadAnimationFrames("smoke-hit", 5);
    auto animation = SpriteLoader::loadAnimation(frames, 0.07, false);
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    sprite->setScale(2.5, 2.5);
    sprite->setPosition(Vec2(300, 140));
    auto animate = Animate::create(animation);
    sprite->runAction(animate);
    addChild(sprite);
}

void DebugAnimationScene::exitScene()
{
    _director->replaceScene(DebugMenuScene::create());
}
