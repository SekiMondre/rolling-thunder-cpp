//
//  Effects.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#include "Effects.h"
#include "RollingThunder.h"

USING_NS_AX;

Node* Effects::createSmokeBurst(int particleCount)
{
//    auto emitter = Node::create();
    
    float lifetime = 0.5;
    
    int randomIdx = 2; // rng
    float randomAngle = 2.3; // rng
    
    auto direction = Vec2(cos(randomAngle), sin(randomAngle));
    auto moveDelta = direction * 45;
    
    // z pos
    
    std::string spriteName = "smoke-particle-";
    spriteName += std::to_string(randomIdx);
    spriteName += ".png";
    auto sprite = SpriteLoader::load(spriteName);
    
    float rotateAngle = 1.5; // rng
    auto rotateBy = RotateBy::create(lifetime, rotateAngle);
    auto moveBy = MoveBy::create(lifetime, moveDelta);
    auto fadeOut = FadeOut::create(lifetime);
//    auto ease = EaseIn::create(fadeOut->clone());
    auto ease = EaseIn::create(fadeOut->clone(), 1);
    
    auto scaleBy = ScaleBy::create(lifetime, 2);
    auto group = Spawn::create(rotateBy, moveBy, fadeOut, scaleBy, nullptr);
    auto destroy = RemoveSelf::create();
    auto sequence = Sequence::createWithTwoActions(group, destroy);
    sprite->runAction(sequence);
    return sprite;
}

Node* Effects::createRockBurst(int particleCount, float radius)
{
//    auto emitter = Node::create();
    
    float lifetime = 1;
    
    int randomIdx = 2; // rng
    float randomAngle = 2.3; // rng
    
    auto direction = Vec2(cos(randomAngle), sin(randomAngle));
    auto moveDelta = direction * 900;
    
    std::string spriteName = "particle-rock-";
    spriteName += std::to_string(randomIdx);
    spriteName += ".png";
    auto sprite = SpriteLoader::load(spriteName);
    
    float rotateAngle = 1.5; // rng
    auto rotate = RotateBy::create(lifetime, rotateAngle);
    auto move = MoveBy::create(lifetime, moveDelta);
    auto group = Spawn::createWithTwoActions(rotate, move);
    auto destroy = RemoveSelf::create();
    auto sequence = Sequence::createWithTwoActions(group, destroy);
    sprite->runAction(sequence);
    return sprite;
}
