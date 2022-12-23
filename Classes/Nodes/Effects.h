//
//  Effects.h
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#ifndef Effects_h
#define Effects_h

#include "axmol.h"

class Effects
{
public:
    static ax::Node* createHitFlash();
    static ax::Node* createDamageFlash();
    static ax::Node* createPowerFlash();
    static ax::Node* createRockExplosion();
    static ax::Node* createTwinkleSparks(const int particleCount, const float interval, const float radius);
    
private:
    Effects();
    static ax::Node* createSmokeBurst(int particleCount);
    static ax::Node* createRockBurst(int particleCount, float radius);
    static ax::Node* createSmokeParticle(float lifetime);
    static ax::Node* createRockParticle(float lifetime);
};

#endif /* Effects_h */
