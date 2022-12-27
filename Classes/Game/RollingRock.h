//
//  RollingRock.h
//  RollingThunderCpp
//
//  Created by André Vants on 27/12/22.
//

#ifndef RollingRock_h
#define RollingRock_h

#include "axmol.h"

enum class Entity;

struct RollingRock
{
    RollingRock(Entity _entityType, ax::Vec2 _direction, float _rollStartFactor);
    
    Entity entityType;
    ax::Vec2 direction;
    float rollStartFactor;
    
    bool operator==(const RollingRock& right) const;
    
    static const RollingRock VERTICAL;
    static const RollingRock DIAGONAL;
};

#endif /* RollingRock_h */
