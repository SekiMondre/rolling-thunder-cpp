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

const float verticalOffset = 30.0f; // TODO: define differently based on device category (phone, pad)
const float movespeed = 3000.0f;
const float bumpMagnitude = 2000.0f;
const float maxDecayFactor = 500.0f;
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
    , _invincible(false)
{}

PlayerNode::~PlayerNode()
{}

bool PlayerNode::init()
{
    if (!Node::init()) return false;
    
    _state = ROLLING; // FIXME
    
    _sprite = SpriteLoader::load("tatu-1-ball-0.png");
    addChild(_sprite);
    
    this->setupPhysicsBody();
    return true;
}

bool PlayerNode::isInvincible() const
{
    return _invincible;
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
            _moveDelta.x = std::lerp(_moveDelta.x, 0.0f, 7.0f * deltaTime);
            _moveDelta.y = std::lerp(_moveDelta.y, 0.0f, 7.0f * deltaTime);
            _decaySpeed.y = std::max(_decaySpeed.y - 20.0f * deltaTime, -maxDecayFactor * deltaTime);
            this->setPosition(this->getPosition().x + _moveDelta.x + _decaySpeed.x,
                              this->getPosition().y + _moveDelta.y + _decaySpeed.y);
        }
        if (_bumpForce != Vec2::ZERO) {
            this->setPosition(this->getPosition().x + _bumpForce.x * deltaTime,
                              this->getPosition().y + _bumpForce.y * deltaTime);
            _bumpForce *= (1.0f - deltaTime);
            if (_bumpForce.length() <= 0.0) {
                _bumpForce = Vec2::ZERO;
            }
        }
        // FIXME: Clamp correctly when game coordinates are resolved
//        this->setPosition(std::clamp(this->getPosition().x, -200.0f, 1200.0f), //std::clamp(this->getPosition().x, -xMoveRange, xMoveRange),
//                          std::clamp(this->getPosition().y, -310.0f, Game::getSceneHeight()));
        
        const float xLimitLeft = Game::getSceneWidth() * 0.5f - xMoveRange;
        const float xLimitRight = Game::getSceneWidth() * 0.5f + xMoveRange;
        
        this->setPosition(std::clamp(this->getPosition().x, xLimitLeft, xLimitRight), //std::clamp(this->getPosition().x, -xMoveRange, xMoveRange),
                          std::clamp(this->getPosition().y, -310.0f, Game::getSceneHeight()));
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

void PlayerNode::applyBump(const Vec2 contactPoint)
{
    if (!_invincible) {
        _internalAcceleration = 0.0f;
        _bumpForce.x = this->getPosition().x - contactPoint.x;
        _bumpForce.y = this->getPosition().y - contactPoint.y;
        _bumpForce.normalize();
        _bumpForce *= bumpMagnitude;
    }
}

void PlayerNode::setupPhysicsBody()
{
    auto physicsBody = PhysicsBody::createCircle(37.0f);
    physicsBody->setDynamic(true);
    physicsBody->setRotationEnable(false);
    physicsBody->setGravityEnable(false);
    physicsBody->setCategoryBitmask(CollisionMask::PLAYER);
    physicsBody->setCollisionBitmask(CollisionMask::NONE);
    physicsBody->setContactTestBitmask(CollisionMask::OBSTACLE | CollisionMask::ENEMY | CollisionMask::COLLECTIBLE);
    setPhysicsBody(physicsBody);
    this->unscheduleUpdate(); // SAGAZ
}
