//
//  Effects.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#include "Effects.h"
#include "RollingThunder.h"

USING_NS_AX;

Node* createSmokeParticle(float lifetime)
{
    int image_idx = URNG::randomInt(1, 3);
    float rotateDegrees = URNG::randomInt(0, 90) - 180; // Intentional angle
    auto moveDelta = URNG::randomDirection() * 45;
    
    auto rotate = RotateBy::create(lifetime, rotateDegrees);
    auto move = MoveBy::create(lifetime, moveDelta);
    auto fadeOut = FadeOut::create(lifetime);
    auto ease = EaseIn::create(fadeOut->clone(), 1);
    auto scale = ScaleBy::create(lifetime, 2);
    auto group = Spawn::create(rotate, move, fadeOut, scale, nullptr);
    auto destroy = RemoveSelf::create();
    auto sequence = Sequence::createWithTwoActions(group, destroy);
    
    std::string spriteName = "smoke-particle-";
    spriteName += std::to_string(image_idx);
    spriteName += ".png";
    auto sprite = SpriteLoader::load(spriteName);
    sprite->runAction(sequence);
    return sprite;
}

Node* createRockParticle(float lifetime)
{
    int image_idx = URNG::randomInt(1, 5);
    float rotateDegrees = URNG::randomInt(0, 360) - 180;
    auto moveDelta = URNG::randomDirection() * 900;
    
    auto rotate = RotateBy::create(lifetime, rotateDegrees);
    auto move = MoveBy::create(lifetime, moveDelta);
    auto group = Spawn::createWithTwoActions(rotate, move);
    auto destroy = RemoveSelf::create();
    auto sequence = Sequence::createWithTwoActions(group, destroy);
    
    std::string spriteName = "particle-rock-";
    spriteName += std::to_string(image_idx);
    spriteName += ".png";
    auto sprite = SpriteLoader::load(spriteName);
    sprite->runAction(sequence);
    return sprite;
}

Node* Effects::createSmokeBurst(int particleCount)
{
    auto emitter = Node::create();
    for (int i = 0; i < particleCount; i++) {
        auto particle = createSmokeParticle(0.5);
        emitter->addChild(particle);
    }
    return emitter;
}

Node* Effects::createRockBurst(int particleCount, float radius)
{
    auto emitter = Node::create();
    for (int i = 0; i < particleCount; i++) {
        auto particle = createRockParticle(1.0);
        particle->setPosition(URNG::randomInsideCircle() * radius);
        emitter->addChild(particle);
    }
    return emitter;
}

Node* Effects::createSmokeHit()
{
    auto frames = SpriteLoader::loadAnimationFrames("smoke-hit", 5);
    auto animation = SpriteLoader::loadAnimation(frames, 0.07, false);
    
    auto animate = Animate::create(animation);
    auto destroy = RemoveSelf::create();
    auto sequence = Sequence::createWithTwoActions(animate, destroy);
    
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    sprite->setScale(2.5, 2.5);
    sprite->runAction(sequence);
    return sprite;
}

Node* Effects::createTwinkleSparks(const int particleCount, const float interval, const float radius)
{
    float lifetime = interval * (particleCount - 1) + 0.56; // 8 frames * 0.07 t
    auto frames = SpriteLoader::loadAnimationFrames("twinkle", 8);
    auto animation = SpriteLoader::loadAnimation(frames, 0.07, false);
    auto emitter = Node::create();
    
    for (int i = 0; i < particleCount; i++)
    {
        auto delay = DelayTime::create(i * interval);
        auto animate = Animate::create(animation);
        auto destroy = RemoveSelf::create();
        auto sequence = Sequence::create(delay, animate, destroy, nullptr);
        
        auto particle = Sprite::create();
        particle->setScale(2.5, 2.5);
        particle->setPosition(URNG::randomInsideCircle() * radius);
        particle->runAction(sequence);
        emitter->addChild(particle);
    }
    
    auto wait = DelayTime::create(lifetime);
    auto destroy = RemoveSelf::create();
    auto waitAndDestroy = Sequence::createWithTwoActions(wait, destroy);
    emitter->runAction(waitAndDestroy);
    return emitter;
}

Node* Effects::createHitFlash()
{
    auto size = Director::getInstance()->getWinSize();
    
    auto overlay = DrawNode::create();
    overlay->drawSolidRect(Vec2::ZERO, size, Color4B::WHITE);
    overlay->setOpacity(204); // 80% alpha
//    sprite->setPositionZ(-9999); // FIXME: When z is defined
    
    auto fade = FadeOut::create(0.1);
    auto destroy = RemoveSelf::create();
    auto sequence = Sequence::createWithTwoActions(fade, destroy);
    overlay->runAction(sequence);
    
    return overlay;
}

Node* Effects::createDamageFlash()
{
    auto size = Director::getInstance()->getWinSize();
    
    auto overlay = DrawNode::create();
    overlay->drawSolidRect(Vec2::ZERO, size, Color4B::RED);
    overlay->setOpacity(178); // 70% alpha
//    sprite->setPositionZ(-9999); // FIXME: When z is defined
    
    auto fade = FadeOut::create(0.1);
    auto destroy = RemoveSelf::create();
    auto sequence = Sequence::createWithTwoActions(fade, destroy);
    overlay->runAction(sequence);
    
    return overlay;
}

Node* Effects::createPowerFlash()
{
    auto size = Director::getInstance()->getWinSize();
    
    auto overlay = DrawNode::create();
    overlay->drawSolidRect(Vec2::ZERO, size, Color4B::WHITE);
//    sprite->setPositionZ(-9999); // FIXME: When z is defined
    
    auto wait = DelayTime::create(0.04);
    auto destroy = RemoveSelf::create();
    auto sequence = Sequence::createWithTwoActions(wait, destroy);
    overlay->runAction(sequence);
    
    return overlay;
}
