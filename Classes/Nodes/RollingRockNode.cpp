//
//  RollingRockNode.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#include "RollingRockNode.h"

USING_NS_AX;

RollingRockNode::RollingRockNode()
{
    // Constructor
}

RollingRockNode::~RollingRockNode()
{
    // Destructor
}

bool RollingRockNode::init()
{
    if (!Node::init()) return false;
    return true;
}