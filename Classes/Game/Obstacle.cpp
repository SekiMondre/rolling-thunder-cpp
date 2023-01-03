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
                                Vec2(114.0f, 114.0f),
                                4
                                );

const Obstacle Obstacle::SMALL(Entity::OBSTACLE_SMALL,
                               Vec2(76.0f, 76.0f),
                               6
                               );

const std::array<Obstacle, 3> Obstacle::ALL = {
    Obstacle::BIG,
    Obstacle::MEDIUM,
    Obstacle::SMALL
};
