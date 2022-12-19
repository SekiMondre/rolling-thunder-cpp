//
//  GameScene.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 13/12/22.
//

#include "GameScene.h"

USING_NS_AX;

GameScene::GameScene()
{
    log("Game scene created");
}

GameScene::~GameScene()
{
    log("Game scene destroyed");
}

bool GameScene::init()
{
    if (!Scene::initWithPhysics()) return false;
    log("Game scene init");
    
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
    
    this->scheduleUpdate();
    return true;
}

void GameScene::update(float deltaTime)
{
//    log("Update delta: %f", deltaTime);
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    log("Touch began location: {%.2f, %.2f}", location.x, location.y);
    return true;
}

void GameScene::onTouchMoved(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    log("Touch moved location: {%.2f, %.2f}", location.x, location.y);
}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    log("Touch ended location: {%.2f, %.2f}", location.x, location.y);
}

void GameScene::onTouchCancelled(Touch* touch, Event* event)
{
//    auto location = touch->getLocation();
}

bool GameScene::onContactBegin(PhysicsContact& contact)
{
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();
    log("contact begin");
    return true;
}
