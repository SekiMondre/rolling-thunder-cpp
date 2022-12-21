//
//  RNG.h
//  RollingThunderCpp
//
//  Created by André Vants on 20/12/22.
//

#ifndef RNG_h
#define RNG_h

#include "axmol.h"

namespace RNG
{
void start();
int randomInt(int min, int max);
float randomUniform();
// TODO: sign, bool
}

namespace URNG
{
int randomInt(int min, int max);
int randomSign();
float randomUniform();
float randomAngle();
ax::Vec2 randomDirection();
ax::Vec2 randomInsideCircle();
}

#endif /* RNG_h */
