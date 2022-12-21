//
//  Effects.h
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#ifndef Effects_h
#define Effects_h

#include "axmol.h"

namespace Effects
{
ax::Node* createSmokeBurst(int particleCount);
ax::Node* createRockBurst(int particleCount, float radius);
ax::Node* createSmokeHit();
}

#endif /* Effects_h */
