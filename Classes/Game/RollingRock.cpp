//
//  RollingRock.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 27/12/22.
//

#include "RollingRock.h"
#include "RollingThunder.h"

USING_NS_AX;

RollingRock::RollingRock(Entity _entityType, Vec2 _direction, float _rollStartFactor)
    : entityType(_entityType)
    , direction(_direction)
    , rollStartFactor(_rollStartFactor)
{}

bool RollingRock::operator==(const RollingRock& right) const
{
    return (entityType == right.entityType);
}

const RollingRock RollingRock::VERTICAL(Entity::ROLLING_ROCK_VERTICAL,
                                        Vec2(0.0f, -1.0f),
                                        1.2f
                                        );
const RollingRock RollingRock::DIAGONAL(Entity::ROLLING_ROCK_DIAGONAL,
                                        Vec2(1.0f, -1.0f),
                                        0.9f
                                        );
