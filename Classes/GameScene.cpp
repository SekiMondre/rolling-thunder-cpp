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
    
    _isTouchEnabled = true;
    
    _GAME = Game::getInstance();
    _GAME->reset();
    
    _score = std::make_unique<ScoreCounter>();
//    _score->setTimeElapsed(0.0f);
    
    auto world = getPhysicsWorld();
    world->setGravity(Vec2(0, 0));
    world->setDebugDrawMask(0xFFFF); // #if DEBUG
    
    _world = World::create();
    addChild(_world);
    
    _player = PlayerNode::create();
    _world->addChild(_player);
//    _world->_updateHierarchy->addChild(_player);
    _player->setPosition(400.0f, 200.0f);
    
    _gui = GUINode::create();
    addChild(_gui);
    
    _gui->setTransitionBeginCallback(std::bind(&GameScene::disableTouch, this));
    _gui->setTransitionEndCallback(std::bind(&GameScene::enableTouch, this));
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = AX_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = AX_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchMoved = AX_CALLBACK_2(GameScene::onTouchMoved, this);
    touchListener->onTouchEnded = AX_CALLBACK_2(GameScene::onTouchEnded, this);
    touchListener->onTouchCancelled = AX_CALLBACK_2(GameScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    this->scheduleUpdate();
    return true;
}

void GameScene::enablePregame()
{
//    _gui->setMainMenuVisible(false);
}

void GameScene::startGame()
{
    // set start time
    // enable world
    // enable player
}

void GameScene::enableTouch()
{
    _isTouchEnabled = true;
}

void GameScene::disableTouch()
{
    _isTouchEnabled = false;
}

void GameScene::update(float deltaTime)
{
    if (_world) {
        _world->update(deltaTime);
    }
    if (_player) {
        _player->update(deltaTime);
    }
    if (_GAME->getState() == GameState::ACTIVE) {
        _score->addTimeElapsed(deltaTime);
        _score->addRunningScore(deltaTime * _GAME->getScrollingSpeed() * 0.3f); // MAGIC rolling factor
    }
    _gui->getHUD()->updateScore(_score->getScore());
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
    if (!_isTouchEnabled) return false;
    
    auto location = touch->getLocation();
    
    // execute any command
    if (_GAME->getState() == GameState::IDLE) {
//        _gui->getMainMenu()->blinkStartLabelWithDelay(0.1f);
        _GAME->setState(GameState::ACTIVE);
        _GAME->setScrollingSpeed(500.0f);
        _player->setRollingState();
        _gui->getMainMenu()->setVisible(false);
        _gui->getHUD()->setVisible(true);
//        _isUserInteractionEnabled = false;
    }
    _player->onInteractionBegin(location);
    
    return true;
}

void GameScene::onTouchMoved(Touch* touch, Event* event)
{
    if (!_isTouchEnabled) return;
    auto location = touch->getLocation();
    _player->onInteractionMoved(location);
}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
    if (!_isTouchEnabled) return;
    auto location = touch->getLocation();
    _player->onInteractionEnded(location);
}

void GameScene::onTouchCancelled(Touch* touch, Event* event)
{
    if (!_isTouchEnabled) return;
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
            
            _score->addComboScore(2000); // MAGIC
            // show score text
            
            if (!player->isInvincible()) {
                _GAME->damagePlayerHealth();
                if (_GAME->getPlayerHealth() > 0) {
                    _player->setInvincibleFrames();
                } else {
                    // game over
                }
                _gui->getHUD()->updateLife(_GAME->getPlayerHealth());
                // play sound
                addChild(Effects::createDamageFlash());
            } else {
                // play sound
                addChild(Effects::createHitFlash());
            }
            nodeB->removeFromParentAndCleanup(true);
        }
        else if (bodyB->getCategoryBitmask() == CollisionMask::ENEMY)
        {
            auto nodeB = bodyB->getNode();
            
            EnemyNode* enemy = static_cast<EnemyNode*>(nodeB);
            
            auto contactPoint = contact.getContactData()->points[0];
            
            // --- hit effect
            nodeB->removeComponent(nodeB->getPhysicsBody());
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
            
            _score->addComboScore(enemy->getType().score);
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
            nodeB->getParent()->addChild(twinkleEmitter);
            
            CollectibleNode* collectible = static_cast<CollectibleNode*>(nodeB);
            
            _score->addMoneyScore(collectible->getType().score, collectible->getType().moneyValue);
            // show score text
            // play sound
            
            // activate power up effect if so
            
            nodeB->removeFromParentAndCleanup(true);
        }
//        else if (bodyB->getCategoryBitmask() == CollisionMask::DEATH_ZONE)
//        {
//            log("player collide...with collectible");
//        }
    }
    
    return true;
}
