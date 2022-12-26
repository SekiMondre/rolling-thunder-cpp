//
//  ObstacleNode.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 14/12/22.
//

#include "ObstacleNode.h"
#include "RollingThunder.h"

USING_NS_AX;

ObstacleNode::ObstacleNode(Obstacle type)
    : _type(type)
    , _sprite(nullptr)
{
//    log("ObstacleNode created");
}

ObstacleNode::~ObstacleNode()
{
    log("ObstacleNode destroyed");
}

ObstacleNode* ObstacleNode::create()
{
    ObstacleNode* node = new ObstacleNode(Obstacle::BIG);
    if (node->init())
    {
        node->autorelease();
        return node;
    }
    delete node;
    node = nullptr;
    return nullptr;
}

ObstacleNode* ObstacleNode::createWithType(Obstacle type)
{
    ObstacleNode* node = new ObstacleNode(type);
    if (node->init())
    {
        node->autorelease();
        return node;
    }
    delete node;
    node = nullptr;
    return nullptr;
}

bool ObstacleNode::init()
{
    if (!Node::init()) return false;
    
    if (_type == Obstacle::SMALL) {
        _sprite = (URNG::randomInt(1, 100) <= 60) ? SpriteLoader::load(ImageAsset::ROCK_SMALL) : SpriteLoader::load(ImageAsset::CACTUS);
    } else if (_type == Obstacle::MEDIUM) {
        _sprite = SpriteLoader::load(ImageAsset::ROCK_MEDIUM);
    } else if (_type == Obstacle::BIG) {
        _sprite = SpriteLoader::load(ImageAsset::ROCK_BIG);
    }
    addChild(_sprite);
    
    this->setupPhysicsBody();
    return true;
}

void ObstacleNode::update(float deltaTime)
{
    this->setPositionY(this->getPositionY() - Game::getInstance()->getScrollingSpeed() * deltaTime);
}

void ObstacleNode::setupPhysicsBody()
{
    auto boxSize = _type.size;
    boxSize.x -= 15;
    boxSize.y -= 20;
    
    auto physicsBody = PhysicsBody::createBox(boxSize);
    physicsBody->setDynamic(true);
    physicsBody->setRotationEnable(false);
    physicsBody->setGravityEnable(false);
    physicsBody->setCategoryBitmask(CollisionMask::OBSTACLE);
    physicsBody->setCollisionBitmask(CollisionMask::NONE);
    physicsBody->setContactTestBitmask(CollisionMask::PLAYER);
    setPhysicsBody(physicsBody);
    this->unscheduleUpdate(); // SAGAZ
}
