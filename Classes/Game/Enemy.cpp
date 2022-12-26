//
//  Enemy.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 26/12/22.
//

#include "Enemy.h"
#include "RollingThunder.h"

USING_NS_AX;

Enemy::Enemy(Entity _entityType, Vec2 _size)
    : entityType(_entityType)
    , size(_size)
{}

bool Enemy::operator==(const Enemy& right) const
{
    return (entityType == right.entityType);
}

const Enemy Enemy::NORMAL(Entity::ENEMY_NORMAL,
                          Vec2(75.0f, 75.0f)
                          );

const Enemy Enemy::BIG(Entity::ENEMY_BIG,
                       Vec2(125.0f, 125.0f)
                       );

const Enemy Enemy::DODGER(Entity::ENEMY_DODGER,
                          Vec2(75.0f, 75.0f)
                          );
