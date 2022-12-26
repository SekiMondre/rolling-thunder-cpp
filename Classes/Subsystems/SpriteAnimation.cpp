//
//  SpriteAnimation.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 23/12/22.
//

#include "SpriteAnimation.h"
#include "SpriteLoader.h"

USING_NS_AX;

const std::string ENEMY_NORMAL = "enemy1-idle";
const std::string ENEMY_BIG = "enemy2-idle";
const std::string GOLD_COIN = "gold_coin";
const std::string SMOKE_HIT = "smoke-hit";

Sprite* SpriteAnimation::createEnemyNormal()
{
    auto frames = SpriteLoader::loadAnimationFrames(ENEMY_NORMAL, 8);
    auto animation = SpriteAnimation::createAnimation(frames, 0.07f, true);
    return SpriteAnimation::createSpriteAnimation(frames, animation);
}

Sprite* SpriteAnimation::createEnemyBig()
{
    auto frames = SpriteLoader::loadAnimationFrames(ENEMY_BIG, 8);
    auto animation = SpriteAnimation::createAnimation(frames, 0.07f, true);
    return SpriteAnimation::createSpriteAnimation(frames, animation);
}

Sprite* SpriteAnimation::createEnemyDodger()
{
    auto frames = SpriteLoader::loadEnemy3Frames();
    auto animation = SpriteAnimation::createAnimation(frames, 0.07f, true);
    return SpriteAnimation::createSpriteAnimation(frames, animation);
}

Sprite* SpriteAnimation::createCrackle()
{
    auto frames = SpriteLoader::loadCrackleFrames();
    auto animation = SpriteAnimation::createAnimation(frames, 0.07f, true);
    return SpriteAnimation::createSpriteAnimation(frames, animation);
}

Sprite* SpriteAnimation::createGoldCoin()
{
    auto frames = SpriteLoader::loadAnimationFrames(GOLD_COIN, 8);
    auto animation = SpriteAnimation::createAnimation(frames, 0.07f, true);
    return SpriteAnimation::createSpriteAnimation(frames, animation);;
}

Sprite* SpriteAnimation::createEphemeralSmokeHit()
{
    auto frames = SpriteLoader::loadAnimationFrames(SMOKE_HIT, 5);
    auto animation = SpriteAnimation::createAnimation(frames, 0.07f, false);
    auto animate = Animate::create(animation);
    auto destroy = RemoveSelf::create();
    auto action = Sequence::createWithTwoActions(animate, destroy);
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    sprite->setScale(2.5f, 2.5f);
    sprite->runAction(action);
    return sprite;
}

Animation* SpriteAnimation::loadPlayerIdleAnimation(const int playerIndex)
{
    auto frames = SpriteLoader::loadPlayerIdleFrames(playerIndex);
    return SpriteAnimation::createAnimation(frames, 0.18f, true);;
}

Animation* SpriteAnimation::loadPlayerRollAnimation(const int playerIndex)
{
    std::string filename = "tatu-" + std::to_string(playerIndex) + "-ball";
    auto frames = SpriteLoader::loadAnimationFrames(filename, 3);
    return SpriteAnimation::createAnimation(frames, 0.07f, true);
}

Animation* SpriteAnimation::loadPlayerDeadAnimation(const int playerIndex)
{
    std::string filename = "tatu-" + std::to_string(playerIndex) + "-dead";
    auto frames = SpriteLoader::loadAnimationFrames(filename, 2);
    return SpriteAnimation::createAnimation(frames, 0.2f, true);
}

Animation* SpriteAnimation::loadEnemy3IdleAnimation()
{
    auto frames = SpriteLoader::loadEnemy3Frames();
    return SpriteAnimation::createAnimation(frames, 0.07f, true);
}

Animation* SpriteAnimation::loadEnemy3DodgeAnimation()
{
    auto frames = SpriteLoader::loadEnemyDodgeFrames();
    return SpriteAnimation::createAnimation(frames, 0.06f, false);
}

Animation* SpriteAnimation::createAnimation(const Vector<SpriteFrame*> frames, const float timePerFrame, const bool loop)
{
    auto animation = Animation::createWithSpriteFrames(frames);
    animation->setDelayPerUnit(timePerFrame);
    if (loop) {
        animation->setLoops(-1);
    } else {
        animation->setLoops(1);
    }
    return animation;
}

Sprite* SpriteAnimation::createSpriteAnimation(const Vector<SpriteFrame*> frames, Animation* const animation)
{
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    sprite->setScale(2.0f, 2.0f);
    sprite->runAction(Animate::create(animation));
    return sprite;
}
