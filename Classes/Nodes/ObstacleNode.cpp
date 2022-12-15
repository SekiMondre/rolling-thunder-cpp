//
//  ObstacleNode.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 14/12/22.
//

#include "ObstacleNode.h"

USING_NS_AX;

ObstacleNode::ObstacleNode()
{
//    _sprite = nullptr;
    log("ObstacleNode created");
}

ObstacleNode::~ObstacleNode()
{
    log("ObstacleNode destroyed");
}

bool ObstacleNode::init()
{
    if (!Node::init()) return false;
    
    _sprite = Sprite::create("sprites/background-1.png");
    addChild(_sprite);
    
    return true;
}
