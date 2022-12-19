//
//  ObstacleNode.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 14/12/22.
//

#include "ObstacleNode.h"
#include "RollingThunder.h"

USING_NS_AX;

Obstacle::Obstacle(std::string _imageName, Vec2 _size) : imageName(_imageName), size(_size) {}

const Obstacle Obstacle::BIG(ROCK_BIG, Vec2(152, 152));
const Obstacle Obstacle::SMALL(ROCK_SMALL, Vec2(77, 77));

// --------------------------------------------------------------------------------

ObstacleNode::ObstacleNode()
    : _sprite(nullptr)
    , _size(Vec2::ZERO)
{
    log("ObstacleNode created");
}

ObstacleNode::~ObstacleNode()
{
    log("ObstacleNode destroyed");
}

ObstacleNode* ObstacleNode::create()
{
    ObstacleNode* node = new ObstacleNode();
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
    ObstacleNode* node = new ObstacleNode();
    if (node)
    {
        // do things
        node->_sprite = SpriteLoader::load(type.imageName);
        node->_size = type.size;
        
        if (node->init())
        {
            node->autorelease();
            return node;
        }
    }
    delete node;
    node = nullptr;
    return nullptr;
}

bool ObstacleNode::init()
{
    if (!Node::init()) return false;
    
    addChild(_sprite);
    
    auto boxSize = _size;
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
    
    return true;
}
