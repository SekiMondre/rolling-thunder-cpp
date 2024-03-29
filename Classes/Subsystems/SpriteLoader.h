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
const std::string GAME_TITLE = "HT-gameTitle.png";

const std::string BACKGROUND = "background-1.png";

const std::string CACTUS = "obst-cactus.png";
const std::string ROLLING_ROCK = "rolling-rock.png";
const std::string ROCK_BIG = "rock-big.png";
const std::string ROCK_MEDIUM = "rock-medium.png";
const std::string ROCK_SMALL = "rock-small.png";
const std::string RUBBISH_BIG = "rubbish-big.png";
const std::string RUBBISH_MEDIUM = "rubbish-medium.png";
const std::string RUBBISH_SMALL = "rubbish-small.png";

const std::string GOLD_COIN = "gold_coin-0.png";
const std::string GOLD_BAR = "gold-bar.png";
const std::string GOLD_BAR_3X = "gold-combo.png";
const std::string SHADOW_33PX = "shadow-33px.png";

const std::string HEART_FULL = "heart-full.png";
const std::string HEART_EMPTY = "heart-empty.png";
const std::string HEART_GOLDEN = "heart-golden.png";
const std::string CLOCK_ICON = "clock.png";

const std::string BUTTON_CREDITS_NORMAL = "button-credits-normal.png";
const std::string BUTTON_CREDITS_PRESSED = "button-credits-active.png";
const std::string BUTTON_RANKING_NORMAL = "button-ranking-normal.png";
const std::string BUTTON_RANKING_PRESSED = "button-ranking-active.png";
const std::string BUTTON_MUSIC_ON_NORMAL = "button-music-on-normal.png";
const std::string BUTTON_MUSIC_ON_PRESSED = "button-music-on-active.png";
const std::string BUTTON_SOUND_ON_NORMAL = "button-sound-on-normal.png";
const std::string BUTTON_SOUND_ON_PRESSED = "button-sound-on-active.png";
const std::string BUTTON_BACK_NORMAL = "button-ok_rank-normal.png";
const std::string BUTTON_BACK_PRESSED = "button-ok_rank-active.png";

const std::string RANKING_WINDOW = "ranking.png";
const std::string CREDITS_WINDOW = "credits.png";
}

class SpriteLoader
{
public:
    friend class SpriteAnimation;
    
    static void start();
    static ax::Sprite* load(std::string name);
    static ax::SpriteFrame* loadFrame(std::string name);
    static ax::Vector<ax::SpriteFrame*> loadAnimationFrames(const std::string name, const int frameCount);
    
private:
    static ax::Vector<ax::SpriteFrame*> loadPlayerIdleFrames(const int playerIndex);
    static ax::Vector<ax::SpriteFrame*> loadCrackleFrames();
    static ax::Vector<ax::SpriteFrame*> loadEnemy3Frames();
    static ax::Vector<ax::SpriteFrame*> loadEnemyDodgeFrames();
};

#endif /* SpriteLoader_h */
