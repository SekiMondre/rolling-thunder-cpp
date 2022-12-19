//
//  DebugCollisionScene.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#include "DebugCollisionScene.h"
#include "Debug.h"

USING_NS_AX;

DebugCollisionScene::DebugCollisionScene()
{}

DebugCollisionScene::~DebugCollisionScene()
{
    log("[DEBUG] Destroying: Collision Test");
}

Node* o;

bool DebugCollisionScene::init()
{
    if (!Scene::initWithPhysics()) return false;
    log("[DEBUG] Init scene: Collision Test");
    
    this->layoutMenu();
    
    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    
    auto root = Node::create();
    root->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, origin.y));
    addChild(root);
    
    // PHYSIX
    auto world = getPhysicsWorld();
    world->setGravity(Vec2(0, 0));
    world->setDebugDrawMask(0xFFFF);
    
    auto body = PhysicsBody::createBox(Vec2(64, 100));
    body->setDynamic(true);
    body->setCategoryBitmask(0x01);
    body->setCollisionBitmask(0x0);
    body->setContactTestBitmask(0xFF);
    
    auto obj = SpriteLoader::load(ROCK_BIG);
    obj->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.5));
    obj->setPhysicsBody(body);
    o = obj;
    
//    root->addChild(obj);
    addChild(obj);
    
    auto body2 = PhysicsBody::createBox(Vec2(48, 48));
    body2->setDynamic(true);
    body2->setCategoryBitmask(0x02);
    body2->setCollisionBitmask(0x00);
    body2->setContactTestBitmask(0x01);
    
    auto rock2 = SpriteLoader::load(ROCK_MEDIUM);
    rock2->setPosition(Vec2(origin.x + visibleSize.width * 0.3, origin.y + visibleSize.height * 0.7));
    rock2->setPhysicsBody(body2);
    
    addChild(rock2);
    
    auto body3 = PhysicsBody::createBox(Vec2(64, 40));
    body3->setDynamic(true);
    body3->setCategoryBitmask(0x03);
    body3->setContactTestBitmask(0x04);
    body3->setCollisionBitmask(0x0);
    
    auto rock3 = SpriteLoader::load(ROCK_SMALL);
    rock3->setPosition(Vec2(origin.x + visibleSize.width * 0.7, origin.y + visibleSize.height * 0.7));
    rock3->setPhysicsBody(body3);
    
    addChild(rock3);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = AX_CALLBACK_1(DebugCollisionScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    // TOUCH
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        auto location = touch->getLocation();
//        log("Touch began location: {%.2f, %.2f}", location.x, location.y);
        o->setPosition(location);
        return true;
    };
    listener->onTouchMoved = [](Touch* touch, Event* event) {
        auto location = touch->getLocation();
//        log("Touch moved location: {%.2f, %.2f}", location.x, location.y);
        o->setPosition(location);
//        return true;
    };
    listener->onTouchEnded = [](Touch* touch, Event* event) {
        auto location = touch->getLocation();
//        log("Touch ended location: {%.2f, %.2f}", location.x, location.y);
//        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool DebugCollisionScene::onContactBegin(PhysicsContact& contact)
{
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();
    log("contact begin");
    return true;
}

void DebugCollisionScene::layoutMenu()
{
    auto exitButton = Debug::createExitButton(AX_CALLBACK_0(DebugCollisionScene::exitScene, this));
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(exitButton);
    auto menu = Menu::createWithArray(menuItems);
    this->addChild(menu);
}

void DebugCollisionScene::exitScene()
{
    _director->replaceScene(DebugMenuScene::create());
}
