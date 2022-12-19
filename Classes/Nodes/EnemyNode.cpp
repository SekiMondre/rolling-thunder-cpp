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
    // Constructor
}

EnemyNode::~EnemyNode()
{
    // Destructor
}

bool EnemyNode::init()
{
    if (!Node::init()) return false;
    
    _sprite = SpriteLoader::load("enemy1-idle-0.png");
    addChild(_sprite);
    
    auto physicsBody = PhysicsBody::createCircle(75 * 0.5);
    physicsBody->setDynamic(true);
    physicsBody->setRotationEnable(false);
    physicsBody->setGravityEnable(false);
    physicsBody->setCategoryBitmask(CollisionMask::ENEMY);
    physicsBody->setCollisionBitmask(CollisionMask::NONE);
    physicsBody->setContactTestBitmask(CollisionMask::PLAYER);
    setPhysicsBody(physicsBody);
    
    return true;
}
