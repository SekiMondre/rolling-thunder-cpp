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
}

Sprite* SpriteLoader::load(std::string name)
{
    auto frame = _cache->getSpriteFrameByName(name);
    if (!frame) {
        log("[ERROR] Could not get sprite frame from cache: %s", name.c_str());
        return nullptr;
    }
    auto sprite = Sprite::createWithSpriteFrame(frame);
    if (!sprite) {
        log("[ERROR] Could not load sprite: %s", name.c_str());
        return nullptr;
    }
//    sprite->getTexture()->setAliasTexParameters(); // Forced NEAREST params in-engine
    sprite->setScale(2.0f, 2.0f);
    return sprite;
}

SpriteFrame* SpriteLoader::loadFrame(std::string name)
{
    auto frame = _cache->getSpriteFrameByName(name);
    if (!frame) {
        log("[ERROR] Could not get sprite frame from cache: %s", name.c_str());
        return nullptr;
    }
    return frame;
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

// MARK: - Private

Vector<SpriteFrame*> SpriteLoader::loadPlayerIdleFrames(const int playerIndex)
{
    std::string basename = "tatu-" + std::to_string(playerIndex) + "-idle-";
    Vector<SpriteFrame*> frames;
    frames.pushBack(_cache->getSpriteFrameByName(basename + "0.png"));
    frames.pushBack(_cache->getSpriteFrameByName(basename + "1.png"));
    frames.pushBack(_cache->getSpriteFrameByName(basename + "2.png"));
    frames.pushBack(_cache->getSpriteFrameByName(basename + "1.png"));
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

Vector<SpriteFrame*> SpriteLoader::loadEnemyDodgeFrames()
{
    Vector<SpriteFrame*> frames;
    frames.pushBack(_cache->getSpriteFrameByName("enemy3-idle-2.png"));
    frames.pushBack(_cache->getSpriteFrameByName("enemy3-idle-1.png"));
    frames.pushBack(_cache->getSpriteFrameByName("enemy3-idle-0.png"));
    frames.pushBack(_cache->getSpriteFrameByName("enemy3-idle-3.png"));
    frames.pushBack(_cache->getSpriteFrameByName("enemy3-idle-4.png"));
    return frames;
}
