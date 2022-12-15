//
//  DebugAnimationScene.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 13/12/22.
//

#include "DebugAnimationScene.h"

USING_NS_AX;

//setName("Debug");
//std::string name{getName()};
//log("Scene init: %s", name.c_str());

//auto rect = DrawNode::create();
//rect->drawSolidRect(origin, Vec2(origin.x + visibleSize.x, origin.y + visibleSize.height), Color4B::BLUE);
//rect->drawLine(Vec2(winSize.width / 2, 0), Vec2(winSize.width / 2, winSize.height), Color4B::RED);
//this->addChild(rect, -1);

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
    
//    auto rect = DrawNode::create();
//    rect->drawSolidRect(origin, Vec2(origin.x + visibleSize.x, origin.y + visibleSize.height), Color4B::BLUE);
//    rect->drawLine(Vec2(winSize.width / 2, 0), Vec2(winSize.width / 2, winSize.height), Color4B::RED);
//    this->addChild(rect, -1);
    
    return true;
}
