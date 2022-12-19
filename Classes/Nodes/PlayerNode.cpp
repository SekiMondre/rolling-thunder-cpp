//
//  PlayerNode.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#include "PlayerNode.h"
#include "RollingThunder.h"

USING_NS_AX;

PlayerNode::PlayerNode()
{}

PlayerNode::~PlayerNode()
{}

bool PlayerNode::init()
{
    if (!Node::init()) return false;
    
    _sprite = SpriteLoader::load("tatu-1-ball-0.png");
    addChild(_sprite);
    
    auto physicsBody = PhysicsBody::createCircle(37);
    physicsBody->setDynamic(true);
    physicsBody->setRotationEnable(false);
    physicsBody->setGravityEnable(false);
    physicsBody->setCategoryBitmask(CollisionMask::PLAYER);
    physicsBody->setCollisionBitmask(CollisionMask::NONE);
    physicsBody->setContactTestBitmask(CollisionMask::OBSTACLE | CollisionMask::ENEMY | CollisionMask::COLLECTIBLE);
    setPhysicsBody(physicsBody);
    
    return true;
}

void PlayerNode::testCall()
{
    log("player node call!!!!!!!!!");
}
