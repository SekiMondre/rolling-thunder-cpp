//
//  GameScene.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 13/12/22.
//

#include "GameScene.h"
#include "RollingThunder.h"

USING_NS_AX;

GameScene::GameScene()
    : _GAME(nullptr)
    , _world(nullptr)
{}

GameScene::~GameScene()
{
    log("Game scene destroyed");
}

bool GameScene::init()
{
    if (!Scene::initWithPhysics()) return false;
    
    _GAME = Game::getInstance();
    
    _score = std::make_unique<ScoreCounter>();
//    _score->setTimeElapsed(0.0f);
    
    auto world = getPhysicsWorld();
    world->setGravity(Vec2(0, 0));
    world->setDebugDrawMask(0xFFFF); // #if DEBUG
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = AX_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = AX_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchMoved = AX_CALLBACK_2(GameScene::onTouchMoved, this);
    touchListener->onTouchEnded = AX_CALLBACK_2(GameScene::onTouchEnded, this);
    touchListener->onTouchCancelled = AX_CALLBACK_2(GameScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    _world = World::create();
    addChild(_world);
    // trigger first spawn?
    
    _player = PlayerNode::create();
    _world->addChild(_player);
//    _world->_updateHierarchy->addChild(_player);
    _player->setPosition(400.0f, 200.0f);
    
    _gui = GUINode::create();
    addChild(_gui);
    
    this->scheduleUpdate();
    return true;
}

//void GameScene::enablePregame()

void GameScene::startGame()
{
    // set start time
    // enable world
    // enable player
}

void GameScene::update(float deltaTime)
{
    // update timer?
    if (_player) {
        _player->update(deltaTime);
    }
    if (_world) {
        _world->update(deltaTime);
    }
    if (_GAME->getState() == GameState::ACTIVE) {
        _score->addTimeElapsed(deltaTime);
        // TODO: update running score
    }
    _gui->getHUD()->updateScore(_score->getScore());
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    
    // execute any command
    if (_GAME->getState() == GameState::IDLE) {
        _GAME->setState(GameState::ACTIVE);
        _GAME->setScrollingSpeed(500.0f);
    }
    _player->onInteractionBegin(location);
    
    return true;
}

void GameScene::onTouchMoved(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    _player->onInteractionMoved(location);
}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    _player->onInteractionEnded(location);
}

void GameScene::onTouchCancelled(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    _player->onInteractionCancelled(location);
}

bool GameScene::onContactBegin(PhysicsContact& contact)
{
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();
    
    if (bodyA->getCategoryBitmask() > bodyB->getCategoryBitmask())
    {
        bodyA = contact.getShapeB()->getBody();
        bodyB = contact.getShapeA()->getBody();
    }
    
    if (bodyA->getCategoryBitmask() == CollisionMask::PLAYER)
    {
        auto node = bodyA->getNode();
        
//        PlayerNode* player = static_cast<PlayerNode*>(node);
        PlayerNode* player = (PlayerNode*)node;
        
        if (bodyB->getCategoryBitmask() == CollisionMask::OBSTACLE)
        {
            auto nodeB = bodyB->getNode();
            
            // crush
            if (nodeB->getTag() == 42) { // SAGAZ
                auto rubbish = MovingNode::create();
                rubbish->setPosition(nodeB->getPosition());
                nodeB->getParent()->addChild(rubbish);
                
                auto obstacle = (ObstacleNode*)nodeB;
                auto type = obstacle->getType();
                if (type == Obstacle::BIG) {
                    rubbish->setSprite(SpriteLoader::load(ImageAsset::RUBBISH_BIG));
                } else if (type == Obstacle::MEDIUM) {
                    rubbish->setSprite(SpriteLoader::load(ImageAsset::RUBBISH_MEDIUM));
                } else if (type == Obstacle::SMALL) {
                    rubbish->setSprite(SpriteLoader::load(ImageAsset::RUBBISH_SMALL));
                }
            }
            
            // particles
            auto explosionEffect = Effects::createRockExplosion();
            explosionEffect->setPosition(nodeB->getPosition());
            _world->_updateHierarchy->addChild(explosionEffect);
            
            // add score
            // show score text
            
            if (!player->isInvincible()) {
                _GAME->damagePlayerHealth();
                if (_GAME->getPlayerHealth() > 0) {
                    // set invincible frames
                } else {
                    // game over
                }
                // update life bar
                // play sound
                addChild(Effects::createDamageFlash());
            } else {
                // play sound
                addChild(Effects::createHitFlash());
            }
            nodeB->removeFromParent();
        }
        else if (bodyB->getCategoryBitmask() == CollisionMask::ENEMY)
        {
            auto nodeB = bodyB->getNode();
            
            EnemyNode* enemy = static_cast<EnemyNode*>(nodeB);
            
            auto contactPoint = contact.getContactData()->points[0];
            
            // --- hit effect
            nodeB->removeComponent(nodeB->getPhysicsBody());
//            auto localContact = _world->_updateHierarchy->convertToNodeSpace(contactPoint);
            auto localContact = nodeB->getParent()->convertToNodeSpace(contactPoint);
            auto direction = (nodeB->getPosition() - localContact).getNormalized();
            auto move = MoveBy::create(2, direction * 3000); // 3000
            auto rotate = RotateBy::create(2, URNG::randomSign() * 3 * 360);
            auto launch = Spawn::createWithTwoActions(move, rotate);
            auto destroy = RemoveSelf::create();
            auto knockOff = Sequence::createWithTwoActions(launch, destroy);
//            nodeB->stopAllActions(); // does nothing | test collision during dodge / remove actions running on sprite
            nodeB->runAction(knockOff); // Needs to disable extra collision
            // --- end hit effect
            
            // add score
            // show score text
            // play sound
            
            if (enemy->getType() == Enemy::BIG && !player->isInvincible()) {
                player->applyBump(contactPoint);
            }
            addChild(Effects::createHitFlash());
        }
        else if (bodyB->getCategoryBitmask() == CollisionMask::COLLECTIBLE)
        {
            auto nodeB = bodyB->getNode();
            
            // TODO: twinkle only if is money
            auto twinkleEmitter = Effects::createTwinkleSparks(4, 0.1, 30);
            twinkleEmitter->setPosition(nodeB->getPosition());
            addChild(twinkleEmitter);
            
            // add score
            // show score text
            // play sound
            
            // activate power up effect if so
        }
//        else if (bodyB->getCategoryBitmask() == CollisionMask::DEATH_ZONE)
//        {
//            log("player collide...with collectible");
//        }
    }
    
    return true;
}
