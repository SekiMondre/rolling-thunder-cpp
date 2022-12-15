//
//  CollectibleNode.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#include "CollectibleNode.h"

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
    return true;
}