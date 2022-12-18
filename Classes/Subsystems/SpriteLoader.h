//
//  SpriteLoader.h
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#ifndef SpriteLoader_h
#define SpriteLoader_h

#include "axmol.h"

const std::string BACKGROUND = "background-1.png";

const std::string ROCK_BIG = "rock-big.png";
const std::string ROCK_MEDIUM = "rock-medium.png";
const std::string ROCK_SMALL = "rock-small.png";

const std::string GOLD_BAR_3X = "gold-combo.png";

const std::string GOLD_COIN = "gold_coin";
const std::string ENEMY_COMMON = "enemy1-idle";
const std::string ENEMY_BIG = "enemy2-idle";

class SpriteLoader
{
public:
    static void start();
    static ax::Sprite* load(std::string_view name);
    static ax::Sprite* loadAnimated(std::string name, int frameCount);
    static ax::Animation* loadAnimation(const ax::Vector<ax::SpriteFrame*> frames, const float timePerFrame = 0.07);
    static ax::Vector<ax::SpriteFrame*> loadAnimationFrames(const std::string name, const int frameCount);
    
    static ax::Sprite* loadPlayerIdle();
    static ax::Sprite* loadPlayerDead();
    static ax::Sprite* loadAnimatedEnemy3();
    static ax::Sprite* loadAnimatedCrackle();
    
private:
    static ax::Sprite* createAnimatedSprite(const ax::Vector<ax::SpriteFrame*> frames, ax::Animation* animation);
    static ax::Vector<ax::SpriteFrame*> loadPlayerIdleFrames();
    static ax::Vector<ax::SpriteFrame*> loadEnemy3Frames();
    static ax::Vector<ax::SpriteFrame*> loadCrackleFrames();
};

#endif /* SpriteLoader_h */
