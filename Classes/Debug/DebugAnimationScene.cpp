//
//  DebugAnimationScene.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 13/12/22.
//

#include "DebugAnimationScene.h"

USING_NS_AX;

bool DebugAnimationScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
//    this->setAnchorPoint(Vec2(0.5, 0));
    
    auto anchor = getAnchorPoint();
    auto absAnchor = getAnchorPointInPoints();
    log("Scene Anchor point: {%.1f, %.1f}", anchor.x, anchor.y);
    log("Scene Anchor pixel: {%.1f, %.1f}", absAnchor.x, absAnchor.y);
    
    auto visibleSize = _director->getVisibleSize();
    auto origin      = _director->getVisibleOrigin();
    auto winSize = _director->getWinSize();
//    auto winOrigin = winSize.origin;
    
    setName("Debug");
    std::string name{getName()};
    log("Scene init: %s", name.c_str());
    auto size = _contentSize;
    log("Content size: {%.1f, %.1f}", size.x, size.y);
//    log("Visible size: {%.1f, %.1f}", visibleSize.x, visibleSize.y);
//    log("Window size: {%.1f, %.1f}", winSize.x, winSize.y);
//    log("Origin: {%.1f, %.1f}", origin.x, origin.y);
    
    auto root = Node::create();
    root->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, origin.y));
    addChild(root);
    
    auto bg = Sprite::create("sprites/background-1.png");
//    auto bg = Sprite::create("background-1.png");
//    auto bg = Sprite::create("HelloWorld.png");
    if (bg == nullptr) {
        log("ERROR!!!!!");
    }
    
    bg->setAnchorPoint(Vec2(0.5, 0));
//    auto bgAnchor = bg->getAnchorPoint();
//    log("BG Anchor point: {%.1f, %.1f}", bgAnchor.x, bgAnchor.y);
    
//    bg->setPosition(Vec2(0, 0));
//    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
//    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, 0));
//    bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
//    bg->setPosition(Vec2(origin.x, origin.y));
//    bg->setPosition(Vec2(360, 0));
    root->addChild(bg);
    
    auto bgSize = bg->getContentSize();
    log("Background size: {%.1f, %.1f}", bgSize.x, bgSize.y);
    
    auto rect = DrawNode::create();
    rect->drawSolidRect(origin, Vec2(origin.x + visibleSize.x, origin.y + visibleSize.height), Color4B::BLUE);
    rect->drawLine(Vec2(visibleSize.width / 2, 0), Vec2(winSize.width / 2, winSize.height), Color4B::RED);
    this->addChild(rect, -1);
    
    return true;
}
