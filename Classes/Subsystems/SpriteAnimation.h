//
//  SpriteAnimation.h
//  RollingThunderCpp
//
//  Created by André Vants on 23/12/22.
//

#ifndef SpriteAnimation_h
#define SpriteAnimation_h

#include "axmol.h"

class SpriteAnimation
{
public:
    static ax::Sprite* createEnemyNormal();
    static ax::Sprite* createEnemyBig();
    static ax::Sprite* createEnemyDodger();
    static ax::Sprite* createCrackle();
    static ax::Sprite* createGoldCoin();
    static ax::Sprite* createEphemeralSmokeHit();
    
    static ax::Animation* loadPlayerIdleAnimation(const int playerIndex);
    static ax::Animation* loadPlayerRollAnimation(const int playerIndex);
    static ax::Animation* loadPlayerDeadAnimation(const int playerIndex);
    
    static ax::Animation* createAnimation(const ax::Vector<ax::SpriteFrame*> frames, const float timePerFrame, const bool loop);
    
private:
    SpriteAnimation();
    
    static ax::Sprite* createSpriteAnimation(const ax::Vector<ax::SpriteFrame*> frames, ax::Animation* const animation);
};

#endif /* SpriteAnimation_h */
