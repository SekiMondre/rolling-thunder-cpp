//
//  EnemyNode.cpp
//  ConvertUTF
//
//  Created by André Vants on 15/12/22.
//

#include "EnemyNode.h"
#include "RollingThunder.h"

USING_NS_AX;

EnemyNode::EnemyNode()
    : _type(NORMAL)
    , _sprite(nullptr)
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
    
    this->setupPhysicsBody();
    return true;
}

void EnemyNode::setType(const Enemy type)
{
    _type = type;
    
    if (_sprite) {
        _sprite->removeFromParent();
    }
    _sprite = SpriteAnimation::createEnemyDodger(); // force
    addChild(_sprite);
}

void EnemyNode::update(float deltaTime)
{
    this->setPositionY(this->getPositionY() - Game::getInstance()->getScrollingSpeed() * deltaTime);
    
    if (_type == DODGER && !_hasDodged) {
        // dodge
    }
}

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

void EnemyNode::simpleDodge()
{
    if (getPositionX() < 0.0f) {
        dodge(1);
    } else {
        dodge(-1);
    }
}

void EnemyNode::spawnAfterimage()
{
    float duration = 0.2f;
    auto ghostSprite = Sprite::createWithSpriteFrame(_sprite->getSpriteFrame());
    ghostSprite->setScale(_sprite->getScale());
    ghostSprite->setColor(Color3B::BLUE);
//    ghostSprite->setBlendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED);
//    ghostSprite->setOpacity(145); // 57%
    ghostSprite->setOpacity(65);
    ghostSprite->runAction(FadeOut::create(duration));
    
    auto afterimage = MovingNode::create();
    afterimage->setSprite(ghostSprite);
    afterimage->setPosition(getPosition());
    auto waitAndDestroy = Sequence::createWithTwoActions(DelayTime::create(duration), RemoveSelf::create());
    afterimage->runAction(waitAndDestroy);
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
