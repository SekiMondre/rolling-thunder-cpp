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
    Enemy(Entity _entityType, ax::Vec2 _size, int _score);
    
    Entity entityType;
    ax::Vec2 size;
    int score;
    
    bool operator==(const Enemy& right) const;
    
    static const Enemy NORMAL;
    static const Enemy BIG;
    static const Enemy DODGER;
    static const std::array<Enemy, 3> ALL;
};

#endif /* Enemy_h */
