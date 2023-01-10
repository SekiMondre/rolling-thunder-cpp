//
//  CollectibleNode.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#include "CollectibleNode.h"
#include "RollingThunder.h"

USING_NS_AX;

CollectibleNode::CollectibleNode(Collectible type)
    : _type(type)
    , _sprite(nullptr)
{}

CollectibleNode::~CollectibleNode()
{
//    log("CollectibleNode destroyed");
}

CollectibleNode* CollectibleNode::createWithType(Collectible type)
{
    CollectibleNode* node = new CollectibleNode(type);
    if (node->init())
    {
        node->autorelease();
        return node;
    }
    delete node;
    node = nullptr;
    return nullptr;
}

const Collectible& CollectibleNode::getType() const
{
    return _type;
}

bool CollectibleNode::init()
{
    if (!Node::init()) return false;
    
    if (_type == Collectible::CRACKLE) {
        _sprite = SpriteAnimation::createCrackle();
    } else if (_type == Collectible::GOLD_BAR) {
        _sprite = SpriteLoader::load(ImageAsset::GOLD_BAR);
    } else if (_type == Collectible::GOLD_BAR_3X) {
        _sprite = SpriteLoader::load(ImageAsset::GOLD_BAR_3X);
    } else { // MONEY
        _sprite = SpriteAnimation::createGoldCoin();
    }
    addChild(_sprite);
    
    this->setupPhysicsBody();
    return true;
}

void CollectibleNode::update(float deltaTime)
{
    this->setPositionY(this->getPositionY() - Game::getInstance()->getScrollingSpeed() * deltaTime);
}

void CollectibleNode::setupPhysicsBody()
{
    auto physicsBody = PhysicsBody::createCircle(_type.size.width * 0.5f);
    physicsBody->setDynamic(true);
    physicsBody->setRotationEnable(false);
    physicsBody->setGravityEnable(false);
    physicsBody->setCategoryBitmask(CollisionMask::COLLECTIBLE);
    physicsBody->setCollisionBitmask(CollisionMask::NONE);
    physicsBody->setContactTestBitmask(CollisionMask::PLAYER);
    setPhysicsBody(physicsBody);
    this->unscheduleUpdate(); // SAGAZ
}
