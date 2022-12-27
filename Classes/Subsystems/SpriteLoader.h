//
//  SpriteLoader.h
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#ifndef SpriteLoader_h
#define SpriteLoader_h

#include "axmol.h"

namespace ImageAsset
{
const std::string BACKGROUND = "background-1.png";
const std::string ROCK_BIG = "rock-big.png";
const std::string ROCK_MEDIUM = "rock-medium.png";
const std::string ROCK_SMALL = "rock-small.png";
const std::string CACTUS = "obst-cactus.png";
const std::string ROLLING_ROCK = "rolling-rock.png";
const std::string GOLD_BAR = "gold-bar.png";
const std::string GOLD_BAR_3X = "gold-combo.png";
const std::string SHADOW_33PX = "shadow-33px.png";
}

class SpriteLoader
{
public:
    friend class SpriteAnimation;
    
    static void start();
    static ax::Sprite* load(std::string name);
    static ax::Vector<ax::SpriteFrame*> loadAnimationFrames(const std::string name, const int frameCount);
    
private:
    static ax::Vector<ax::SpriteFrame*> loadPlayerIdleFrames(const int playerIndex);
    static ax::Vector<ax::SpriteFrame*> loadCrackleFrames();
    static ax::Vector<ax::SpriteFrame*> loadEnemy3Frames();
    static ax::Vector<ax::SpriteFrame*> loadEnemyDodgeFrames();
};

#endif /* SpriteLoader_h */
