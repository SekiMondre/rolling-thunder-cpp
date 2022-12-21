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

Node* _playerNode;

bool DebugCollisionScene::init()
{
    if (!Scene::initWithPhysics()) return false;
    log("[DEBUG] Init scene: Collision Test");
    
    this->layoutMenu();
    
    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    
//    auto root = Node::create();
//    root->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, origin.y));
//    addChild(root);
    
    // PHYSIX
    auto world = getPhysicsWorld();
    world->setGravity(Vec2(0, 0));
    world->setDebugDrawMask(0xFFFF);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = AX_CALLBACK_1(DebugCollisionScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    // TOUCH
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        auto location = touch->getLocation();
        _playerNode->setPosition(location);
        return true;
    };
    listener->onTouchMoved = [](Touch* touch, Event* event) {
        auto location = touch->getLocation();
        _playerNode->setPosition(location);
    };
    listener->onTouchEnded = [](Touch* touch, Event* event) {
        auto location = touch->getLocation();
//        log("Touch ended location: {%.2f, %.2f}", location.x, location.y);
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->resetNodes();
    
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
            
            // TODO: pack effect into a single node
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
            auto nodeB = bodyB->getNode();
            
            log("player collide...with enemy");
            auto contactPoint = contact.getContactData()->points[0];
            
            auto direction = (nodeB->getPosition() - contactPoint).getNormalized();
            auto move = MoveBy::create(2, direction * 3000);
            auto rotate = RotateBy::create(2, URNG::randomSign() * 3 * 360);
            auto launch = Spawn::createWithTwoActions(move, rotate);
            auto destroy = RemoveSelf::create();
            auto knockOff = Sequence::createWithTwoActions(launch, destroy);
//            nodeB->stopAllActions(); // does nothing
            nodeB->runAction(knockOff); // Needs to disable extra collision
        }
        else if (bodyB->getCategoryBitmask() == CollisionMask::COLLECTIBLE)
        {
            auto nodeB = bodyB->getNode();
            
            auto twinkleEmitter = Effects::createTwinkleSparks(4, 0.1, 30); // twinkle if is money
            twinkleEmitter->setPosition(nodeB->getPosition());
            addChild(twinkleEmitter);
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
    auto visibleSize = _director->getVisibleSize();
    
    auto exitButton = Debug::createExitButton(AX_CALLBACK_0(DebugCollisionScene::exitScene, this));
    
    auto resetButton = Debug::createColorButton("R", 32, Vec2(64, 64), Color4B::BLUE);
    resetButton->setPosition(Vec2(visibleSize.width * 0.5 - 32 - 16, -visibleSize.height * 0.5 + 32 + 16));
    resetButton->setCallback(AX_CALLBACK_0(DebugCollisionScene::resetNodes, this));
    
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(exitButton);
    menuItems.pushBack(resetButton);
    auto menu = Menu::createWithArray(menuItems);
    this->addChild(menu);
}

void DebugCollisionScene::resetNodes()
{
    _playerNode = nullptr;
    removeAllChildren();
    
    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    
    auto small = ObstacleNode::createWithType(Obstacle::SMALL);
    small->setPosition(Vec2(origin.x + visibleSize.width * 0.3, origin.y + visibleSize.height * 0.7));
    addChild(small);
    
    auto enemy = EnemyNode::create();
    enemy->setPosition(Vec2(origin.x + visibleSize.width * 0.7, origin.y + visibleSize.height * 0.7));
    addChild(enemy);
    
    auto big = ObstacleNode::createWithType(Obstacle::BIG);
    big->setPosition(Vec2(origin.x + visibleSize.width * 0.4, origin.y + visibleSize.height * 0.3));
    addChild(big);
    
    auto gold = CollectibleNode::create();
    gold->setPosition(Vec2(origin.x + visibleSize.width * 0.75, origin.y + visibleSize.height * 0.25));
    addChild(gold);
    
    auto player = PlayerNode::create();
    player->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.5));
    addChild(player);
    _playerNode = player;
    
    this->layoutMenu();
}

void DebugCollisionScene::exitScene()
{
    _director->replaceScene(DebugMenuScene::create());
}
