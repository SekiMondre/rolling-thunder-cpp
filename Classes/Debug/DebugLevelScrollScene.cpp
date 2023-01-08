//
//  DebugLevelScrollScene.cpp
//  ConvertUTF
//
//  Created by André Vants on 22/12/22.
//

#include "DebugLevelScrollScene.h"
#include "Debug.h"
#include "RollingThunder.h"

USING_NS_AX;

DebugLevelScrollScene::DebugLevelScrollScene()
    : _world(nullptr)
{}

DebugLevelScrollScene::~DebugLevelScrollScene()
{
    log("[DEBUG] Destroying: Level Scroll Test");
}

bool DebugLevelScrollScene::init()
{
    if (!Scene::initWithPhysics()) return false;
    log("[DEBUG] Init scene: Level Scroll Test");
    
    _world = World::create();
    addChild(_world);
    
    this->layoutMenu();
    this->scheduleUpdate();
    
    Game::getInstance()->setScrollingSpeed(500.0f);
    Game::getInstance()->setState(GameState::ACTIVE);
    
    return true;
}

void DebugLevelScrollScene::update(float deltaTime)
{
    if (_world) {
        _world->update(deltaTime);
    }
}

void DebugLevelScrollScene::layoutMenu()
{
    auto exitButton = Debug::createExitButton(AX_CALLBACK_0(DebugLevelScrollScene::exitScene, this));
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(exitButton);
    auto menu = Menu::createWithArray(menuItems);
    this->addChild(menu);
}

void DebugLevelScrollScene::exitScene()
{
    _director->replaceScene(DebugMenuScene::create());
}

//// spawn test ---------- on world update
//static float count = 0.0;
//count += deltaTime;
//if (count > 2.5f)
//{
//    count = 0.0;
//    
//    auto o1 = ObstacleNode::createWithType(Obstacle::BIG);
//    o1->setPosition(-152.0f, Game::getSceneHeight() + 200);
//    _updateHierarchy->addChild(o1);
//
//    auto o2 = ObstacleNode::createWithType(Obstacle::MEDIUM);
//    o2->setPosition(-0.0f, Game::getSceneHeight() + 500);
//    _updateHierarchy->addChild(o2);
//
//    auto o3 = ObstacleNode::createWithType(Obstacle::SMALL);
//    o3->setPosition(76.0f, Game::getSceneHeight() + 800);
//    _updateHierarchy->addChild(o3);
//
//    auto c1 = CollectibleNode::createWithType(Collectible::MONEY);
//    c1->setPosition(-150.0f, Game::getSceneHeight() + 100);
//    _updateHierarchy->addChild(c1);
//    auto c2 = CollectibleNode::createWithType(Collectible::GOLD_BAR);
//    c2->setPosition(-50.0f, Game::getSceneHeight() + 100);
//    _updateHierarchy->addChild(c2);
//    auto c3 = CollectibleNode::createWithType(Collectible::GOLD_BAR_3X);
//    c3->setPosition(50.0f, Game::getSceneHeight() + 100);
//    _updateHierarchy->addChild(c3);
//    auto c4 = CollectibleNode::createWithType(Collectible::CRACKLE);
//    c4->setPosition(150.0f, Game::getSceneHeight() + 100);
//    _updateHierarchy->addChild(c4);
//    
//    auto e1 = EnemyNode::createWithType(Enemy::BIG);
//    e1->setPosition(-100.0f, Game::getSceneHeight() + 380);
//    _updateHierarchy->addChild(e1);
//
//    auto e2 = EnemyNode::createWithType(Enemy::NORMAL);
//    e2->setPosition(100.0f, Game::getSceneHeight() + 380);
//    _updateHierarchy->addChild(e2);
//    
//    auto r1 = RollingRockNode::createWithType(RollingRock::DIAGONAL);
//    r1->setPosition(-190, Game::getSceneHeight() + 1100);
//    _updateHierarchy->addChild(r1);
//
//    auto r2 = RollingRockNode::createWithType(RollingRock::DIAGONAL);
//    r2->setPosition(190, Game::getSceneHeight() + 600);
//    _updateHierarchy->addChild(r2);
//
//    auto r3 = RollingRockNode::createWithType(RollingRock::VERTICAL);
//    r3->setPosition(150, Game::getSceneHeight() + 500);
//    _updateHierarchy->addChild(r3);
//}
//// end test ----------
