//
//  RNG.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 20/12/22.
//

#include "RNG.h"

USING_NS_AX;

inline int randomize()
{
    return rand();
}

// MARK: Random Number Generation

void RNG::start()
{
    srand((unsigned int)time(0));
}

// Max-exclusive
int RNG::randomInt(int min, int max)
{
    return (randomize() % (max - min)) + min;
}

float RNG::randomUniform()
{
    return (float(randomize())/float(RAND_MAX));
}

// MARK: Unseeded Random Number Generation

// Max-inclusive
int URNG::randomInt(int min, int max)
{
    return RandomHelper::random_int(min, max);
}

float URNG::randomUniform()
{
    return RandomHelper::random_real(0.0, 1.0);
}

float URNG::randomAngle()
{
    return randomUniform() * M_PI * 2;
}

Vec2 URNG::randomDirection()
{
    float angle = randomAngle();
    return Vec2(cos(angle), sin(angle));
}

Vec2 URNG::randomInsideCircle()
{
    return randomDirection() * randomUniform();
}
