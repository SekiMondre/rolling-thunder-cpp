//
//  RollingRockNode.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#include "RollingRockNode.h"
#include "RollingThunder.h"

USING_NS_AX;

const float X_SPEED_FACTOR = 0.65f;
const float Y_SPEED_FACTOR = 0.4f;

const float BASE_BOUNCE_SPEED = 30.0f;
const float BOUNCE_GRAVITY = 2000.0f;

const float SHADOW_OFFSET = -40.0f;

RollingRockNode::RollingRockNode(RollingRock type)
    : _type(type)
    , _sprite(nullptr)
    , _shadowSprite(nullptr)
    , _direction(Vec2::ZERO)
    , _isRolling(false)
    , _rollStartFactor(0.0f)
    , _bounceSpeed(0.0f)
    , _rotationSpeed(0.0f)
{}

RollingRockNode::~RollingRockNode()
{
    log("RollingRockNode destroyed");
}

RollingRockNode* RollingRockNode::createWithType(RollingRock type)
{
    RollingRockNode* node = new RollingRockNode(type);
    if (node->init())
    {
        node->autorelease();
        return node;
    }
    delete node;
    node = nullptr;
    return nullptr;
}

bool RollingRockNode::init()
{
    if (!Node::init()) return false;
    
    _direction.x = _type.direction.x;
    _direction.y = _type.direction.y;
    _rollStartFactor = _type.rollStartFactor;
    
//    _sprite = SpriteLoader::load(ImageAsset::ROLLING_ROCK);
//    addChild(_sprite);
    
    _shadowSprite = SpriteLoader::load(ImageAsset::SHADOW_33PX); // FIXME: Z position
    _shadowSprite->setPositionY(SHADOW_OFFSET);
    addChild(_shadowSprite);
    
    _sprite = SpriteLoader::load(ImageAsset::ROLLING_ROCK);
    addChild(_sprite);
    
    this->setupPhysicsBody();
    return true;
}

void RollingRockNode::update(float deltaTime)
{
    float scrollSpeed = Game::getInstance()->getScrollingSpeed();
    this->setPositionY(getPositionY() - scrollSpeed * deltaTime);
    if (_isRolling)
    {
        this->setPositionX(getPositionX() + scrollSpeed * deltaTime * X_SPEED_FACTOR * _direction.x);
        this->setPositionY(getPositionY() + scrollSpeed * deltaTime * Y_SPEED_FACTOR * _direction.y);
        _bounceSpeed -= BOUNCE_GRAVITY * deltaTime;
        _sprite->setPositionY(_sprite->getPositionY() + _bounceSpeed * deltaTime);
        _sprite->setRotation(_sprite->getRotation() + _rotationSpeed * deltaTime);
        if (_sprite->getPositionY() < 0.0f) {
            _sprite->setPositionY(0.0f);
            this->bounce();
            if (URNG::randomBool()) {
                _sprite->setScaleX(_sprite->getScaleX() * -1.0f);
            }
            if (URNG::randomBool()) {
                _sprite->setScaleY(_sprite->getScaleY() * -1.0f);
            }
        }
    }
    else if (getPositionY() < Game::getSceneHeight() * _rollStartFactor)
    {
        _isRolling = true;
        if (_type == RollingRock::DIAGONAL) {
            _direction.x = (getPositionX() < 0.0f) ? 1.0f : -1.0f;
        }
        this->bounce();
    }
}

void RollingRockNode::bounce()
{
    _bounceSpeed = sqrt(2.0f * BASE_BOUNCE_SPEED * BOUNCE_GRAVITY); // Smart impulse formula
    _rotationSpeed = URNG::randomUniform() * 2.0f * 360.0f; // Angle in degrees
    
    if (_parent) {
        auto smoke = Effects::createSmokeBurst(5); // FIXME: effect node leak / Also, needs to move with the world
        smoke->setPosition(this->_parent->convertToNodeSpace(this->convertToWorldSpace(_shadowSprite->getPosition())));
        this->_parent->addChild(smoke);
    }
}

void RollingRockNode::setupPhysicsBody()
{
    auto physicsBody = PhysicsBody::createCircle(92.0f * 0.5f - 10.0f); // FIXME: Magic number
    physicsBody->setDynamic(true);
    physicsBody->setRotationEnable(false);
    physicsBody->setGravityEnable(false);
    physicsBody->setCategoryBitmask(CollisionMask::OBSTACLE);
    physicsBody->setCollisionBitmask(CollisionMask::NONE);
    physicsBody->setContactTestBitmask(CollisionMask::PLAYER);
    setPhysicsBody(physicsBody);
    this->unscheduleUpdate(); // SAGAZ
}
