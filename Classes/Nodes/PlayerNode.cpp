//
//  PlayerNode.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#include "PlayerNode.h"
#include "RollingThunder.h"
#include <algorithm>

USING_NS_AX;

const float verticalOffset = 30.0f;
const float movespeed = 3000.0f;
const float xMoveRange = 195.0f;

PlayerNode::PlayerNode()
    : _state(INACTIVE)
    , _sprite(nullptr)
    , _touchPosition(Vec2::ZERO)
    , _velocity(Vec2::ZERO)
    , _direction(Vec2::ZERO)
    , _moveDelta(Vec2::ZERO)
    , _decaySpeed(Vec2::ZERO)
    , _bumpForce(Vec2::ZERO)
    , _internalAcceleration(0.0f)
{}

PlayerNode::~PlayerNode()
{}

bool PlayerNode::init()
{
    if (!Node::init()) return false;
    
    _sprite = SpriteLoader::load("tatu-1-ball-0.png");
    addChild(_sprite);
    
    auto physicsBody = PhysicsBody::createCircle(37.0f);
    physicsBody->setDynamic(true);
    physicsBody->setRotationEnable(false);
    physicsBody->setGravityEnable(false);
    physicsBody->setCategoryBitmask(CollisionMask::PLAYER);
    physicsBody->setCollisionBitmask(CollisionMask::NONE);
    physicsBody->setContactTestBitmask(CollisionMask::OBSTACLE | CollisionMask::ENEMY | CollisionMask::COLLECTIBLE);
    setPhysicsBody(physicsBody);
    setPosition(Vec2::ZERO);
    
    _state = ROLLING;
    
    return true;
}

void PlayerNode::update(float deltaTime)
{
    if (_state == ROLLING)
    {
        if (_touchPosition != Vec2::ZERO) {
            _internalAcceleration = std::min(_internalAcceleration + deltaTime, 1.0f);
            _direction.x = _touchPosition.x - this->getPosition().x;
            _direction.y = _touchPosition.y - this->getPosition().y;
            _direction.normalize();
            _velocity = _direction * movespeed * _internalAcceleration;
            _moveDelta = _velocity * deltaTime;
            if (_moveDelta.length() > this->getPosition().distance(_touchPosition)) {
                _moveDelta.x = _touchPosition.x - this->getPosition().x;
                _moveDelta.y = _touchPosition.y - this->getPosition().y;
            }
            this->setPosition(this->getPosition().x + _moveDelta.x,
                              this->getPosition().y + _moveDelta.y);
        } else {
            _internalAcceleration = std::max(_internalAcceleration - 2.0f * deltaTime, 0.0f);
            _moveDelta.x = std::lerp(_moveDelta.x, 0.0f, 7 * deltaTime);
            _moveDelta.y = std::lerp(_moveDelta.y, 0.0f, 7 * deltaTime);
            _decaySpeed.y = std::max(_decaySpeed.y - 20.0f * deltaTime, -500.0f * deltaTime);
            this->setPosition(this->getPosition().x + _moveDelta.x + _decaySpeed.x,
                              this->getPosition().y + _moveDelta.y + _decaySpeed.y);
        }
        if (_bumpForce != Vec2::ZERO) {
            // bump
        }
//        this->setPosition(std::clamp(this->getPosition().x, -xMoveRange, xMoveRange),
//                          std::clamp(this->getPosition().y, -310, 1000)); // SceneSize.height
    }
}

void PlayerNode::onInteractionBegin(const Vec2 touchLocation)
{
    _touchPosition.x = touchLocation.x;
    _touchPosition.y = touchLocation.y + verticalOffset;
}

void PlayerNode::onInteractionMoved(const Vec2 touchLocation)
{
    _touchPosition.x = touchLocation.x;
    _touchPosition.y = touchLocation.y + verticalOffset;
}

void PlayerNode::onInteractionEnded(const Vec2 touchLocation)
{
    _touchPosition.x = 0.0f;
    _touchPosition.y = 0.0f;
    _decaySpeed.x = 0.0f;
    _decaySpeed.y = 0.0f;
}

void PlayerNode::onInteractionCancelled(const Vec2 touchLocation)
{
    _touchPosition.x = 0.0f;
    _touchPosition.y = 0.0f;
    _decaySpeed.x = 0.0f;
    _decaySpeed.y = 0.0f;
}
