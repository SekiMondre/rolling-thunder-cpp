//
//  Effects.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#include "Effects.h"
#include "RollingThunder.h"

USING_NS_AX;

// MARK: - Public

Node* Effects::createHitFlash()
{
    auto size = Director::getInstance()->getWinSize();
    
    auto overlay = DrawNode::create();
    overlay->drawSolidRect(Vec2::ZERO, size, Color4B::WHITE);
    overlay->setOpacity(204); // 80% alpha
//    sprite->setPositionZ(-9999); // FIXME: When z is defined
    
    auto fade = FadeOut::create(0.1f);
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
    
    auto fade = FadeOut::create(0.1f);
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
    
    auto wait = DelayTime::create(0.04f);
    auto destroy = RemoveSelf::create();
    auto sequence = Sequence::createWithTwoActions(wait, destroy);
    overlay->runAction(sequence);
    
    return overlay;
}

Node* Effects::createRockExplosion()
{
    auto smokeEmitter = Effects::createSmokeBurst(8);
    auto rockEmitter = Effects::createRockBurst(5, 50);
    auto smokeHit = SpriteAnimation::createEphemeralSmokeHit();
    auto container = Node::create(); // TODO: Needs clean up from scene
    container->addChild(smokeEmitter);
    container->addChild(rockEmitter);
    container->addChild(smokeHit);
    return container;
}

Node* Effects::createSmokeBurst(int particleCount)
{
    auto emitter = Node::create();
    for (int i = 0; i < particleCount; i++) {
        auto particle = createSmokeParticle(0.5f);
        emitter->addChild(particle);
    }
    return emitter;
}

Node* Effects::createTwinkleSparks(const int particleCount, const float interval, const float radius)
{
    float lifetime = interval * (particleCount - 1.0f) + 0.56f; // 8 frames * 0.07 t
    auto frames = SpriteLoader::loadAnimationFrames("twinkle", 8);
    auto animation = SpriteAnimation::createAnimation(frames, 0.07f, false);
    auto emitter = Node::create();
    
    for (int i = 0; i < particleCount; i++)
    {
        auto delay = DelayTime::create(i * interval);
        auto animate = Animate::create(animation);
        auto destroy = RemoveSelf::create();
        auto sequence = Sequence::create(delay, animate, destroy, nullptr);
        
        auto particle = Sprite::create();
        particle->setScale(2.5f, 2.5f);
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

// MARK: - Private

Node* Effects::createRockBurst(int particleCount, float radius)
{
    auto emitter = Node::create();
    for (int i = 0; i < particleCount; i++) {
        auto particle = createRockParticle(1.0f);
        particle->setPosition(URNG::randomInsideCircle() * radius);
        emitter->addChild(particle);
    }
    return emitter;
}

Node* Effects::createSmokeParticle(float lifetime)
{
    int image_idx = URNG::randomInt(1, 3);
    float rotateDegrees = (float)(URNG::randomInt(0, 90) - 180); // Intentional angle
    auto moveDelta = URNG::randomDirection() * 45.0f;
    
    auto rotate = RotateBy::create(lifetime, rotateDegrees);
    auto move = MoveBy::create(lifetime, moveDelta);
    auto fadeOut = FadeOut::create(lifetime);
    auto ease = EaseIn::create(fadeOut->clone(), 1.0f);
    auto scale = ScaleBy::create(lifetime, 2.0f);
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

Node* Effects::createRockParticle(float lifetime)
{
    int image_idx = URNG::randomInt(1, 5);
    float rotateDegrees = (float)(URNG::randomInt(0, 360) - 180);
    auto moveDelta = URNG::randomDirection() * 900.0f;
    
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
