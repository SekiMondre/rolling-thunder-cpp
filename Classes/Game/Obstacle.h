//
//  Obstacle.h
//  RollingThunderCpp
//
//  Created by André Vants on 26/12/22.
//

#ifndef Obstacle_h
#define Obstacle_h

#include "axmol.h"

enum class Entity;

struct Obstacle
{
    Obstacle(Entity _entityType, ax::Vec2 _size, int _slotCount);
    
    Entity entityType;
    ax::Vec2 size;
    int slotCount;
    float slotCorrectionFactor;
    
    bool operator==(const Obstacle& right) const;
    
    static const Obstacle BIG;
    static const Obstacle MEDIUM;
    static const Obstacle SMALL;
    static const std::array<Obstacle, 3> ALL;
};

#endif /* Obstacle_h */
