//
//  SpriteLoader.h
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#ifndef SpriteLoader_h
#define SpriteLoader_h

#include "axmol.h"

class SpriteLoader
{
public:
    static ax::Sprite* createBackground();
    static ax::Sprite* createRock();
    static ax::Sprite* createCoinAnimation();
};

#endif /* SpriteLoader_h */
