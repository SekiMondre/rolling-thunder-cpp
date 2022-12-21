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
    
    auto player = PlayerNode::create();
    player->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.5));
    o = player;
//    log("Player bitmask: %x", player->getPhysicsBody()->getContactTestBitmask());
    
//    root->addChild(obj);
    addChild(player);
    
    auto rock2 = ObstacleNode::createWithType(Obstacle::SMALL);
    rock2->setPosition(Vec2(origin.x + visibleSize.width * 0.3, origin.y + visibleSize.height * 0.7));
    addChild(rock2);
    
    auto rock3 = EnemyNode::create();
    rock3->setPosition(Vec2(origin.x + visibleSize.width * 0.7, origin.y + visibleSize.height * 0.7));
    addChild(rock3);
    
    auto node = ObstacleNode::createWithType(Obstacle::BIG);
    node->setPosition(Vec2(origin.x + visibleSize.width * 0.4, origin.y + visibleSize.height * 0.3));
    addChild(node);
    
    auto gold = CollectibleNode::create();
    gold->setPosition(Vec2(origin.x + visibleSize.width * 0.75, origin.y + visibleSize.height * 0.25));
    addChild(gold);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = AX_CALLBACK_1(DebugCollisionScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    // TOUCH
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        auto location = touch->getLocation();
        o->setPosition(location);
        return true;
    };
    listener->onTouchMoved = [](Touch* touch, Event* event) {
        auto location = touch->getLocation();
        o->setPosition(location);
    };
    listener->onTouchEnded = [](Touch* touch, Event* event) {
        auto location = touch->getLocation();
//        log("Touch ended location: {%.2f, %.2f}", location.x, location.y);
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool DebugCollisionScene::onContactBegin(PhysicsContact& contact)
{
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();
//    auto nodeA = bodyA->getNode();
    
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
//        player->testCall();
        
        if (bodyB->getCategoryBitmask() == CollisionMask::OBSTACLE)
        {
            auto nodeB = bodyB->getNode();
            
            auto smokeEmitter = Effects::createSmokeBurst(8);
            smokeEmitter->setPosition(nodeB->getPosition());
            addChild(smokeEmitter);
            auto rockEmitter = Effects::createRockBurst(5, 50);
            rockEmitter->setPosition(nodeB->getPosition());
            addChild(rockEmitter);
            auto smokeHit = Effects::createSmokeHit();
            smokeHit->setPosition(nodeB->getPosition());
            addChild(smokeHit);
        }
        else if (bodyB->getCategoryBitmask() == CollisionMask::ENEMY)
        {
            log("player collide...with enemy");
        }
        else if (bodyB->getCategoryBitmask() == CollisionMask::COLLECTIBLE)
        {
            log("player collide...with collectible");
        }
//        else if (bodyB->getCategoryBitmask() == CollisionMask::DEATH_ZONE)
//        {
//            log("player collide...with collectible");
//        }
    }
    
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
