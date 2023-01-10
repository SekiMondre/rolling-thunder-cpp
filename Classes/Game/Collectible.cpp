//
//  Collectible.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 27/12/22.
//

#include "Collectible.h"
#include "RollingThunder.h"

USING_NS_AX;

Collectible::Collectible(Entity _entityType, Vec2 _size, int _score, int _moneyValue)
    : entityType(_entityType)
    , size(_size)
    , score(_score)
    , moneyValue(_moneyValue)
{}

bool Collectible::operator==(const Collectible& right) const
{
    return (entityType == right.entityType);
}

const Collectible Collectible::MONEY(Entity::COLLECT_MONEY,
                                     Vec2(60.0f, 60.0f),
                                     200,
                                     1
                                     );

const Collectible Collectible::GOLD_BAR(Entity::COLLECT_GOLD_BAR,
                                        Vec2(100.0f, 100.0f),
                                        10000,
                                        10
                                        );

const Collectible Collectible::GOLD_BAR_3X(Entity::COLLECT_GOLD_BAR_3X,
                                           Vec2(100.0f, 100.0f),
                                           30000,
                                           30
                                           );

const Collectible Collectible::CRACKLE(Entity::POWER_UP_CRACKLE,
                                       Vec2(100.0f, 100.0f),
                                       5000,
                                       0
                                       );
