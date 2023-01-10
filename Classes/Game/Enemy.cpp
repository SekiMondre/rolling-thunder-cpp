//
//  Enemy.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 26/12/22.
//

#include "Enemy.h"
#include "RollingThunder.h"

USING_NS_AX;

Enemy::Enemy(Entity _entityType, Vec2 _size, int _score)
    : entityType(_entityType)
    , size(_size)
    , score(_score)
{}

bool Enemy::operator==(const Enemy& right) const
{
    return (entityType == right.entityType);
}

const Enemy Enemy::NORMAL(Entity::ENEMY_NORMAL,
                          Vec2(75.0f, 75.0f),
                          1000
                          );

const Enemy Enemy::BIG(Entity::ENEMY_BIG,
                       Vec2(125.0f, 125.0f),
                       3000
                       );

const Enemy Enemy::DODGER(Entity::ENEMY_DODGER,
                          Vec2(75.0f, 75.0f),
                          5000
                          );

const std::array<Enemy, 3> Enemy::ALL = {
    Enemy::NORMAL,
    Enemy::BIG,
    Enemy::DODGER
};
