//
//  CollectibleNode.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#include "CollectibleNode.h"
#include "RollingThunder.h"

USING_NS_AX;

CollectibleNode::CollectibleNode()
{
    // Constructor
}

CollectibleNode::~CollectibleNode()
{
    // Destructor
}

bool CollectibleNode::init()
{
    if (!Node::init()) return false;
    
    _sprite = SpriteLoader::load("gold-bar.png");
    addChild(_sprite);
    
    auto physicsBody = PhysicsBody::createCircle(60 * 0.5);
    physicsBody->setDynamic(true);
    physicsBody->setRotationEnable(false);
    physicsBody->setGravityEnable(false);
    physicsBody->setCategoryBitmask(CollisionMask::COLLECTIBLE);
    physicsBody->setCollisionBitmask(CollisionMask::NONE);
    physicsBody->setContactTestBitmask(CollisionMask::PLAYER);
    setPhysicsBody(physicsBody);
    
    return true;
}
