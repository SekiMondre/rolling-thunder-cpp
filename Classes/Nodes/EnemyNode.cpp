//
//  EnemyNode.cpp
//  ConvertUTF
//
//  Created by André Vants on 15/12/22.
//

#include "EnemyNode.h"
#include "RollingThunder.h"

USING_NS_AX;

EnemyNode::EnemyNode()
{
//    log("EnemyNode created");
}

EnemyNode::~EnemyNode()
{
    log("EnemyNode destroyed");
}

bool EnemyNode::init()
{
    if (!Node::init()) return false;
    
    _sprite = SpriteAnimation::createEnemyNormal();
    addChild(_sprite);
    
    this->setupPhysicsBody();
    return true;
}

void EnemyNode::update(float deltaTime)
{
    this->setPositionY(this->getPositionY() - Game::getInstance()->getScrollingSpeed() * deltaTime);
}

void EnemyNode::setupPhysicsBody()
{
    auto physicsBody = PhysicsBody::createCircle(75 * 0.5);
    physicsBody->setDynamic(true);
    physicsBody->setRotationEnable(false);
    physicsBody->setGravityEnable(false);
    physicsBody->setCategoryBitmask(CollisionMask::ENEMY);
    physicsBody->setCollisionBitmask(CollisionMask::NONE);
    physicsBody->setContactTestBitmask(CollisionMask::PLAYER);
    setPhysicsBody(physicsBody);
    this->unscheduleUpdate(); // SAGAZ
}
