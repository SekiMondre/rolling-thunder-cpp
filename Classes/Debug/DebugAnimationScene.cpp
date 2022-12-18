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

//auto rect = DrawNode::create();
//rect->drawSolidRect(origin, Vec2(origin.x + visibleSize.x, origin.y + visibleSize.height), Color4B::BLUE);
//rect->drawLine(Vec2(winSize.width / 2, 0), Vec2(winSize.width / 2, winSize.height), Color4B::RED);
//this->addChild(rect, -1);

DebugAnimationScene::DebugAnimationScene()
{
    log("[DEBUG] Create scene: DebugAnimation");
}

DebugAnimationScene::~DebugAnimationScene()
{
    log("[DEBUG] Destroy scene: DebugAnimation");
}

bool DebugAnimationScene::init()
{
    if (!Scene::init()) return false;
    
    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    auto winSize = _director->getWinSize();
    
    auto root = Node::create();
    root->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, origin.y));
    addChild(root);
    
//    auto aa = SpriteLoader::BACKGROUND;
    auto bg = SpriteLoader::createBackground();
    bg->setAnchorPoint(Vec2(0.5, 0));
    root->addChild(bg);
    
    auto bgSize = bg->getContentSize();
    log("Background size: {%.1f, %.1f}", bgSize.x, bgSize.y);
    
    auto rock = SpriteLoader::createRock();
    rock->setPosition(Vec2(0, 500));
    root->addChild(rock);
    
    auto coin = SpriteLoader::createCoinAnimation();
    coin->setPosition(Vec2(0, 200));
    root->addChild(coin);
    
    auto exitButton = Debug::createColorButton("X", 32, Vec2(64, 64), Color4B::RED);
    exitButton->setCallback(AX_CALLBACK_0(DebugAnimationScene::exitScene, this));
    exitButton->setPosition(Vec2(-visibleSize.width * 0.5 + 32 + 16, visibleSize.height * 0.5 - 32 - 16));
    
    auto menu = Menu::create(exitButton, NULL);
    this->addChild(menu);
    
    return true;
}

void DebugAnimationScene::exitScene()
{
    _director->replaceScene(DebugMenuScene::create());
}
