//
//  Enemy.h
//  RollingThunderCpp
//
//  Created by André Vants on 26/12/22.
//

#ifndef Enemy_h
#define Enemy_h

#include "axmol.h"

enum class Entity;

struct Enemy
{
    Enemy(Entity _entityType, ax::Vec2 _size);
    
    Entity entityType;
    ax::Vec2 size;
    
    bool operator==(const Enemy& right) const;
    
    static const Enemy NORMAL;
    static const Enemy BIG;
    static const Enemy DODGER;
};

#endif /* Enemy_h */
