//
//  World.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 22/12/22.
//

#include "World.h"
#include "RollingThunder.h"

USING_NS_AX;

World::World()
    : _background_0(nullptr)
    , _background_1(nullptr)
{}

World::~World()
{}

bool World::init()
{
    if (!Node::init()) return false;
    
    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    
    // setup bg
    _background_0 = SpriteLoader::load(BACKGROUND);
    _background_1 = SpriteLoader::load(BACKGROUND);
    _background_0->setAnchorPoint(Vec2(0.5f, 0.0f));
    _background_1->setAnchorPoint(Vec2(0.5f, 0.0f));
    _background_0->setPosition(origin.x + visibleSize.x * 0.5f, 0.0f); // TODO: set z position
    _background_1->setPosition(origin.x + visibleSize.x * 0.5f, _background_0->getContentSize().height * _background_0->getScaleX());
    addChild(_background_0);
    addChild(_background_1);
    
    return true;
}

void World::update(float deltaTime)
{
    float verticalDelta = 500.0f * deltaTime;
    float scaledHeight_0 = _background_0->getContentSize().height * _background_0->getScaleY();
    float scaledHeight_1 = _background_1->getContentSize().height * _background_1->getScaleY();
    float yTarget_0 = _background_0->getPositionY() - verticalDelta;
    float yTarget_1 = _background_1->getPositionY() - verticalDelta;
    
    if (yTarget_0 < -scaledHeight_0) {
        yTarget_0 = yTarget_1 + scaledHeight_0;
    }
    if (yTarget_1 < -scaledHeight_1) {
        yTarget_1 = yTarget_0 + scaledHeight_1;
    }
    _background_0->setPositionY(yTarget_0);
    _background_1->setPositionY(yTarget_1);
}
