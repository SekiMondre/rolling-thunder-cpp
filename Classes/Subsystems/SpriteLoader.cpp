//
//  SpriteLoader.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#include "SpriteLoader.h"

USING_NS_AX;

static SpriteFrameCache* _cache = nullptr;

void SpriteLoader::start()
{
    _cache = SpriteFrameCache::getInstance();
    _cache->addSpriteFramesWithFile("sprites/ht-sprites.plist");
    _cache->addSpriteFramesWithFile("sprites/ui-sprites.plist");
}

Sprite* SpriteLoader::load(std::string_view name)
{
    auto frame = _cache->getSpriteFrameByName(name); // TODO: handle nulls w/ log
    auto sprite = Sprite::createWithSpriteFrame(frame);
//    sprite->getTexture()->setAliasTexParameters(); // Forced NEAREST params in-engine
    sprite->setScale(2, 2);
    return sprite;
}

Sprite* SpriteLoader::loadAnimated(std::string name, int frameCount)
{
    auto frames = loadAnimationFrames(name, frameCount);
    auto animation = loadAnimation(frames);
    auto sprite = createAnimatedSprite(frames, animation);
    return sprite;
}

Animation* SpriteLoader::loadAnimation(const Vector<SpriteFrame*> frames, const float timePerFrame)
{
    auto animation = Animation::createWithSpriteFrames(frames);
    animation->setDelayPerUnit(timePerFrame);
    animation->setLoops(-1);
    return animation;
}

Vector<SpriteFrame*> SpriteLoader::loadAnimationFrames(const std::string name, const int frameCount)
{
    Vector<SpriteFrame*> frames;
    char nameBuffer[64];
    for (int i = 0; i < frameCount; i++) {
        snprintf(nameBuffer, 64, "%s-%d.png", name.c_str(), i);
        frames.pushBack(_cache->getSpriteFrameByName(nameBuffer));
    }
    return frames;
}

Sprite* SpriteLoader::loadPlayerIdle()
{
    auto frames = loadPlayerIdleFrames();
    auto animation = loadAnimation(frames, 0.18);
    auto sprite = createAnimatedSprite(frames, animation);
    return sprite;
}

Sprite* SpriteLoader::loadPlayerDead()
{
    auto frames = loadAnimationFrames("tatu-1-dead", 2);
    auto animation = loadAnimation(frames, 0.2);
    auto sprite = createAnimatedSprite(frames, animation);
    return sprite;
}

Sprite* SpriteLoader::loadAnimatedEnemy3()
{
    auto frames = loadEnemy3Frames();
    auto animation = loadAnimation(frames);
    auto sprite = createAnimatedSprite(frames, animation);
    return sprite;
}

Sprite* SpriteLoader::loadAnimatedCrackle()
{
    auto frames = loadCrackleFrames();
    auto animation = loadAnimation(frames);
    auto sprite = createAnimatedSprite(frames, animation);
    return sprite;
}

// MARK: - Private

Sprite* SpriteLoader::createAnimatedSprite(const Vector<SpriteFrame*> frames, Animation* animation)
{
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    sprite->setScale(2, 2);
    auto animate = Animate::create(animation);
    sprite->runAction(animate);
    return sprite;
}

Vector<SpriteFrame*> SpriteLoader::loadPlayerIdleFrames()
{
    Vector<SpriteFrame*> frames;
    frames.pushBack(_cache->getSpriteFrameByName("tatu-1-idle-0.png"));
    frames.pushBack(_cache->getSpriteFrameByName("tatu-1-idle-1.png"));
    frames.pushBack(_cache->getSpriteFrameByName("tatu-1-idle-2.png"));
    frames.pushBack(_cache->getSpriteFrameByName("tatu-1-idle-1.png"));
    return frames;
}

Vector<SpriteFrame*> SpriteLoader::loadEnemy3Frames()
{
    Vector<SpriteFrame*> frames;
    frames.pushBack(_cache->getSpriteFrameByName("enemy3-idle-0.png"));
    frames.pushBack(_cache->getSpriteFrameByName("enemy3-idle-1.png"));
    frames.pushBack(_cache->getSpriteFrameByName("enemy3-idle-2.png"));
    frames.pushBack(_cache->getSpriteFrameByName("enemy3-idle-1.png"));
    frames.pushBack(_cache->getSpriteFrameByName("enemy3-idle-0.png"));
    frames.pushBack(_cache->getSpriteFrameByName("enemy3-idle-3.png"));
    frames.pushBack(_cache->getSpriteFrameByName("enemy3-idle-4.png"));
    frames.pushBack(_cache->getSpriteFrameByName("enemy3-idle-3.png"));
    return frames;
}

Vector<SpriteFrame*> SpriteLoader::loadCrackleFrames()
{
    Vector<SpriteFrame*> frames;
    frames.pushBack(_cache->getSpriteFrameByName("crackle-0.png"));
    frames.pushBack(_cache->getSpriteFrameByName("crackle-1.png"));
    frames.pushBack(_cache->getSpriteFrameByName("crackle-2.png"));
    frames.pushBack(_cache->getSpriteFrameByName("crackle-1.png"));
    return frames;
}
