//
//  CollisionMask.h
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#ifndef CollisionMask_h
#define CollisionMask_h

#include "axmol.h"

namespace CollisionMask
{
    const int NONE = 0;
    const int PLAYER = 0x01;
    const int OBSTACLE = 0x02;
    const int ENEMY = 0x04;
    const int COLLECTIBLE = 0x08;
//    const int DEATH_ZONE
}

#endif /* CollisionMask_h */
