//
//  NodeFactory.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 26/12/22.
//

#include "NodeFactory.h"

USING_NS_AX;

Node* NodeFactory::parseEntity(const SpawnPoint& spawnPoint)
{
    Node* node = nullptr;
    
    switch (spawnPoint.type)
    {
        case Entity::ENEMY_NORMAL: {
            node = EnemyNode::createWithType(Enemy::NORMAL);;
            break;
        }
        case Entity::ENEMY_BIG: {
            node = EnemyNode::createWithType(Enemy::BIG);;
            break;
        }
        case Entity::ENEMY_DODGER: {
            node = EnemyNode::createWithType(Enemy::DODGER);;
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
        case Entity::ROLLING_ROCK_VERTICAL: {
            node = RollingRockNode::createWithType(RollingRock::VERTICAL);;
            break;
        }
        case Entity::ROLLING_ROCK_DIAGONAL: {
            node = RollingRockNode::createWithType(RollingRock::DIAGONAL);;
            break;
        }
        case Entity::COLLECT_MONEY: {
            node = CollectibleNode::createWithType(Collectible::MONEY);
            break;
        }
        case Entity::COLLECT_GOLD_BAR: {
            node = CollectibleNode::createWithType(Collectible::GOLD_BAR);
            break;
        }
        case Entity::COLLECT_GOLD_BAR_3X: {
            node = CollectibleNode::createWithType(Collectible::GOLD_BAR_3X);
            break;
        }
        case Entity::POWER_UP_CRACKLE: {
            node = CollectibleNode::createWithType(Collectible::CRACKLE);
            break;
        }
        default: {
            log("[ERROR] Parse Entity: Unhandled spawn type.");
            break;
        }
    }
    
    return node;
}
