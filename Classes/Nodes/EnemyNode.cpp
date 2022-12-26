//
//  EnemyNode.cpp
//  ConvertUTF
//
//  Created by André Vants on 15/12/22.
//

#include "EnemyNode.h"
#include "RollingThunder.h"

USING_NS_AX;

const float DODGE_THRESHOLD = 230.0f;
const float CENTER_THRESHOLD = 50.0f;

// TODO: Correctly setup needed values based on type

EnemyNode::EnemyNode()
    : _type(NORMAL)
    , _sprite(nullptr)
    , _hasDodged(false)
{}

EnemyNode::~EnemyNode()
{
    log("EnemyNode destroyed");
}

bool EnemyNode::init()
{
    if (!Node::init()) return false;
    
    _sprite = SpriteAnimation::createEnemyNormal();
    addChild(_sprite);
    
    this->setupPhysicsBody(); // Needs to set physics after having a type (box size)
    return true;
}

void EnemyNode::setType(const Enemy type)
{
    _type = type;
    
    if (_sprite) {
        _sprite->stopAllActions();
        _sprite->removeFromParent();
    }
    
    if (_type == DODGER) {
        _sprite = SpriteAnimation::createEnemyDodger();
    } else if (_type == BIG) {
        _sprite = SpriteAnimation::createEnemyBig();
    } else {
        _sprite = SpriteAnimation::createEnemyNormal();
    }
    addChild(_sprite);
    
    if (URNG::randomBool()) {
        _sprite->setScaleX(_sprite->getScaleX() * -1);
    }
}

void EnemyNode::update(float deltaTime)
{
    this->setPositionY(this->getPositionY() - Game::getInstance()->getScrollingSpeed() * deltaTime);
    
    if (_type == DODGER && !_hasDodged) {
        auto playerPosition = Vec2::ZERO; // TODO: get player node position
        if (getPositionY() - playerPosition.y < DODGE_THRESHOLD) {
            int direction = 0;
            if (abs(getPositionX()) < CENTER_THRESHOLD) {
                direction = (getPositionX() < playerPosition.x) ? -1 : 1; // Near the center, dodge relative to player
            } else {
                direction = (getPositionX() < 0.0f) ? 1 : -1; // Outer lanes, dodge to farthest wall
            }
            dodge(direction);
            _hasDodged = true;
        }
    }
}

void EnemyNode::simpleDodge()
{
    if (getPositionX() < 0.0f) {
        dodge(1);
    } else {
        dodge(-1);
    }
}

// MARK: - Private

void EnemyNode::dodge(const int direction)
{
    float dodgeDistance = abs(180.0f * (float)direction - getPositionX());
    float maxDistance = 180 + 100;
    float duration = 0.5f * dodgeDistance / maxDistance; // Yea, don't ask me, again
    
    auto move = MoveTo::create(duration, Vec2(180.0f * (float)direction, getPositionY()));
    auto easeMove = EaseOut::create(move->clone(), 1.2f);
    auto spawnImage = CallFunc::create(AX_CALLBACK_0(EnemyNode::spawnAfterimage, this));
    auto wait = DelayTime::create(0.07f);
    auto leaveAfterimages = Repeat::create(Sequence::createWithTwoActions(spawnImage, wait), int(0.5f / 0.075f));
    auto dodge = Spawn::createWithTwoActions(easeMove, leaveAfterimages);
    
    auto animateDodge = Animate::create(SpriteAnimation::loadEnemy3DodgeAnimation());
    auto animateIdle = Animate::create(SpriteAnimation::loadEnemy3IdleAnimation());
    auto animate = Sequence::create(animateDodge, DelayTime::create(0.35f), animateIdle, nullptr);
    
    _sprite->stopAllActions();
    this->stopAllActions();
    _sprite->runAction(animate);
    this->runAction(dodge);
}

void EnemyNode::spawnAfterimage()
{
    float duration = 0.2f;
    auto ghostSprite = Sprite::createWithSpriteFrame(_sprite->getSpriteFrame());
    ghostSprite->setScaleX(_sprite->getScaleX());
    ghostSprite->setScaleY(_sprite->getScaleY());
    ghostSprite->setColor(Color3B::BLUE);
//    ghostSprite->setBlendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED);
//    ghostSprite->setOpacity(145); // 57%
    ghostSprite->setOpacity(65);
    ghostSprite->runAction(FadeOut::create(duration));
    
    auto afterimage = MovingNode::createEphemeral(duration);
    afterimage->setSprite(ghostSprite);
    afterimage->setPosition(getPosition());
    if (_parent) {
        _parent->addChild(afterimage);
    }
}

void EnemyNode::setupPhysicsBody()
{
    auto physicsBody = PhysicsBody::createCircle(75 * 0.5);
    physicsBody->setDynamic(true);
    physicsBody->setRotationEnable(false);
    physicsBody->setGravityEnable(false);
    physicsBody->setCategoryBitmask(CollisionMask::ENEMY);
    physicsBody->setCollisionBitmask(CollisionMask::NONE);
    physicsBody->setContactTestBitmask(CollisionMask::PLAYER);
    setPhysicsBody(physicsBody);
    this->unscheduleUpdate(); // SAGAZ
}
