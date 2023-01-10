//
//  Collectible.h
//  RollingThunderCpp
//
//  Created by André Vants on 27/12/22.
//

#ifndef Collectible_h
#define Collectible_h

#include "axmol.h"

enum class Entity;

struct Collectible
{
    Collectible(Entity _entityType, ax::Vec2 _size, int _score, int _moneyValue);
    
    Entity entityType;
    ax::Vec2 size;
    int score;
    int moneyValue;
    
    bool operator==(const Collectible& right) const;
    
    static const Collectible MONEY;
    static const Collectible GOLD_BAR;
    static const Collectible GOLD_BAR_3X;
    static const Collectible CRACKLE;
};

#endif /* Collectible_h */
