//
//  MovingNode.cpp
//  ConvertUTF
//
//  Created by André Vants on 25/12/22.
//

#include "MovingNode.h"
#include "RollingThunder.h"

USING_NS_AX;

MovingNode::MovingNode()
    : _sprite(nullptr)
{}

MovingNode::~MovingNode()
{
    log("Moving node destroyed");
}

MovingNode* MovingNode::createEphemeral(const float lifetime)
{
    auto node = MovingNode::create();
    auto waitAndDestroy = Sequence::createWithTwoActions(DelayTime::create(lifetime), RemoveSelf::create());
    node->runAction(waitAndDestroy);
    return node;
}

bool MovingNode::init()
{
    if (!Node::init()) return false;
    return true;
}

void MovingNode::setSprite(Sprite* const sprite)
{
    if (_sprite == nullptr) {
        _sprite = sprite;
        addChild(_sprite);
    }
}

void MovingNode::update(float deltaTime)
{
    this->setPositionY(this->getPositionY() - Game::getInstance()->getScrollingSpeed() * deltaTime);
}
