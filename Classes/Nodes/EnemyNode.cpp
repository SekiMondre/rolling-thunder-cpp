//
//  EnemyNode.cpp
//  ConvertUTF
//
//  Created by André Vants on 15/12/22.
//

#include "EnemyNode.h"

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
    return true;
}