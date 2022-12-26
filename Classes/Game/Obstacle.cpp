//
//  Obstacle.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 26/12/22.
//

#include "Obstacle.h"
#include "RollingThunder.h"

USING_NS_AX;

Obstacle::Obstacle(Entity _entityType, Vec2 _size, int _slotCount)
    : entityType(_entityType)
    , size(_size)
    , slotCount(_slotCount)
{
    slotCorrectionFactor = float(_slotCount - 1) * 0.5f;
}

bool Obstacle::operator==(const Obstacle& right) const
{
    return (entityType == right.entityType); // Only want to look for entity equality
}

const Obstacle Obstacle::BIG(Entity::OBSTACLE_BIG,
                             Vec2(152.0f, 152.0f),
                             3
                             );

const Obstacle Obstacle::MEDIUM(Entity::OBSTACLE_MEDIUM,
                                Vec2(115.0f, 115.0f),
                                4
                                );

const Obstacle Obstacle::SMALL(Entity::OBSTACLE_SMALL,
                               Vec2(77.0f, 77.0f),
                               6
                               );
