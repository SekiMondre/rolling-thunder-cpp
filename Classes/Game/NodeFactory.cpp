//
//  NodeFactory.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 26/12/22.
//

#include "NodeFactory.h"

USING_NS_AX;

Node* NodeFactory::parseEntity(const SpawnPoint spawnPoint)
{
    Node* node = nullptr;
    
    switch (spawnPoint.type)
    {
        case Entity::ENEMY_NORMAL: {
            auto enemy = EnemyNode::create();
            enemy->setType(Enemy::NORMAL);
            node = enemy;
            break;
        }
        case Entity::OBSTACLE_BIG: {
            node = ObstacleNode::createWithType(Obstacle::BIG);;
            break;
        }
        case Entity::OBSTACLE_MEDIUM: {
            node = ObstacleNode::createWithType(Obstacle::MEDIUM);;
            break;
        }
        case Entity::OBSTACLE_SMALL: {
            node = ObstacleNode::createWithType(Obstacle::SMALL);;
            break;
        }
        default: {
            log("UNHANDLED TYPE!!!");
            break;
        }
    }
    
    return node;
}
