//
//  DebugLevelSectionScene.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#include "DebugLevelSectionScene.h"
#include "Debug.h"
#include "RollingThunder.h"

USING_NS_AX;

DebugLevelSectionScene::DebugLevelSectionScene()
{
    float w = Director::getInstance()->getWinSize().width * 0.75f;
    float h = Director::getInstance()->getWinSize().height;
    float spacing = 152.0f;
    _levelGen = new LevelGenerator(w, h, spacing);
}

DebugLevelSectionScene::~DebugLevelSectionScene()
{
    delete _levelGen;
    log("[DEBUG] Destroying: Level Modules Test");
}

bool DebugLevelSectionScene::init()
{
    if (!Scene::initWithPhysics()) return false;
    getPhysicsWorld()->setDebugDrawMask(0xFFFF);
    
    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    
    auto bg = SpriteLoader::load(ImageAsset::BACKGROUND);
    bg->setAnchorPoint(Vec2(0.5, 0));
    bg->setPosition(origin.x + visibleSize.width * 0.5, 0);
    addChild(bg);
    
    auto root = Node::create();
    root->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, origin.y));
    addChild(root);
    _root = root;
    
    this->layoutMenu();
    return true;
}

void DebugLevelSectionScene::layoutMenu()
{
    auto visibleSize = _director->getVisibleSize();
    
    auto exitButton = Debug::createExitButton(AX_CALLBACK_0(DebugLevelSectionScene::exitScene, this));
    
    const auto fSize = 31;
    const auto bSize = Vec2(64, 64);
    const auto bWidth = bSize.width;
    const auto b_x0 = visibleSize.width * 0.5;
    
    auto button1a = Debug::createColorButton("Ox1", fSize, bSize, Color4B::BLUE);
    auto button1b = Debug::createColorButton("Ox2", fSize, bSize, Color4B::BLUE);
    auto button1c = Debug::createColorButton("Ox3", fSize, bSize, Color4B::BLUE);
    auto button1d = Debug::createColorButton("Ox4", fSize, bSize, Color4B::BLUE);
    
    auto button2a = Debug::createColorButton("E1", fSize, bSize, Color4B::BLUE);
    auto button2b = Debug::createColorButton("E2", fSize, bSize, Color4B::BLUE);
    auto button2c = Debug::createColorButton("E3", fSize, bSize, Color4B::BLUE);
    auto button2d = Debug::createColorButton("E4", fSize, bSize, Color4B::BLUE);
    
    auto button3a = Debug::createColorButton("Rx1", fSize, bSize, Color4B::BLUE);
    auto button3b = Debug::createColorButton("Rx1+", fSize, bSize, Color4B::BLUE);
    auto button3c = Debug::createColorButton("Rx3", fSize, bSize, Color4B::BLUE);
    
    auto button4a = Debug::createColorButton("Pow", fSize, bSize, Color4B::BLUE);
    auto button4b = Debug::createColorButton("C", fSize, bSize, Color4B::BLUE);
    
    const auto h1 = -visibleSize.height * 0.5 + bSize.height * 0.5f + 16;
    button1a->setPosition(Vec2(b_x0 - (bWidth + 16) * 0 - bWidth * 0.5f - 16, h1));
    button1b->setPosition(Vec2(b_x0 - (bWidth + 16) * 1 - bWidth * 0.5f - 16, h1));
    button1c->setPosition(Vec2(b_x0 - (bWidth + 16) * 2 - bWidth * 0.5f - 16, h1));
    button1d->setPosition(Vec2(b_x0 - (bWidth + 16) * 3 - bWidth * 0.5f - 16, h1));
    
    const auto h2 = -visibleSize.height * 0.5 + bSize.height * 1.5f + 16 * 2;
    button2a->setPosition(Vec2(b_x0 - (bWidth + 16) * 0 - bWidth * 0.5f - 16, h2));
    button2b->setPosition(Vec2(b_x0 - (bWidth + 16) * 1 - bWidth * 0.5f - 16, h2));
    button2c->setPosition(Vec2(b_x0 - (bWidth + 16) * 2 - bWidth * 0.5f - 16, h2));
    button2d->setPosition(Vec2(b_x0 - (bWidth + 16) * 3 - bWidth * 0.5f - 16, h2));
    
    const auto h3 = -visibleSize.height * 0.5 + bSize.height * 2.5f + 16 * 3;
    button3a->setPosition(Vec2(b_x0 - (bWidth + 16) * 0 - bWidth * 0.5f - 16, h3));
    button3b->setPosition(Vec2(b_x0 - (bWidth + 16) * 1 - bWidth * 0.5f - 16, h3));
    button3c->setPosition(Vec2(b_x0 - (bWidth + 16) * 2 - bWidth * 0.5f - 16, h3));
    
    const auto h4 = -visibleSize.height * 0.5 + bSize.height * 3.5f + 16 * 4;
    button4a->setPosition(Vec2(b_x0 - (bWidth + 16) * 0 - bWidth * 0.5f - 16, h4));
    button4b->setPosition(Vec2(b_x0 - (bWidth + 16) * 1 - bWidth * 0.5f - 16, h4));
    
    button1a->setCallback(AX_CALLBACK_0(DebugLevelSectionScene::test1a, this));
    button1b->setCallback(AX_CALLBACK_0(DebugLevelSectionScene::test1b, this));
    button1c->setCallback(AX_CALLBACK_0(DebugLevelSectionScene::test1c, this));
    button1d->setCallback(AX_CALLBACK_0(DebugLevelSectionScene::test1d, this));
    
    button2a->setCallback(AX_CALLBACK_0(DebugLevelSectionScene::test2a, this));
    button2b->setCallback(AX_CALLBACK_0(DebugLevelSectionScene::test2b, this));
    button2c->setCallback(AX_CALLBACK_0(DebugLevelSectionScene::test2c, this));
    button2d->setCallback(AX_CALLBACK_0(DebugLevelSectionScene::test2d, this));
    
    button3a->setCallback(AX_CALLBACK_0(DebugLevelSectionScene::test3a, this));
    button3b->setCallback(AX_CALLBACK_0(DebugLevelSectionScene::test3b, this));
    button3c->setCallback(AX_CALLBACK_0(DebugLevelSectionScene::test3c, this));
    
    button4a->setCallback(AX_CALLBACK_0(DebugLevelSectionScene::test4a, this));
    button4b->setCallback(AX_CALLBACK_0(DebugLevelSectionScene::test4b, this));
    
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(exitButton);
    
    menuItems.pushBack(button1a);
    menuItems.pushBack(button1b);
    menuItems.pushBack(button1c);
    menuItems.pushBack(button1d);
    
    menuItems.pushBack(button2a);
    menuItems.pushBack(button2b);
    menuItems.pushBack(button2c);
    menuItems.pushBack(button2d);
    
    menuItems.pushBack(button3a);
    menuItems.pushBack(button3b);
    menuItems.pushBack(button3c);
    
    menuItems.pushBack(button4a);
    menuItems.pushBack(button4b);
    auto menu = Menu::createWithArray(menuItems);
    this->addChild(menu);
}

void DebugLevelSectionScene::resetSpawn(const std::list<SpawnPoint>& spawns)
{
    _root->removeAllChildren();
    for (const auto &e : spawns) {
        auto node = NodeFactory::parseEntity(e);
        node->setPosition(e.position);
        _root->addChild(node);
    }
}

//void DebugLevelSectionScene::action1()
//{
//    _root->removeAllChildren();
//
//    static bool hasGEN = false;
//    if (!hasGEN) {
//        hasGEN = true;
//        _levelGen->generateLevel(3, 10);
//    }
//    std::list<SpawnPoint> spawns = _levelGen->popNextSection();
//
//    for (const auto &e : spawns) {
//        auto node = NodeFactory::parseEntity(e);
//        node->setPosition(e.position);
//        _root->addChild(node);
//    }
//}

void DebugLevelSectionScene::test1a()
{
    std::list<SpawnPoint> spawns;
    _levelGen->spawnObstacles(spawns, 1, false);
    resetSpawn(spawns);
}

void DebugLevelSectionScene::test1b()
{
    std::list<SpawnPoint> spawns;
    _levelGen->spawnObstacles(spawns, 2, false);
    resetSpawn(spawns);
}

void DebugLevelSectionScene::test1c()
{
    std::list<SpawnPoint> spawns;
    _levelGen->spawnObstacles(spawns, 3, false);
    resetSpawn(spawns);
}

void DebugLevelSectionScene::test1d()
{
    std::list<SpawnPoint> spawns;
    _levelGen->spawnObstacles(spawns, 4, false);
    resetSpawn(spawns);
}

void DebugLevelSectionScene::test2a()
{
    std::list<SpawnPoint> spawns;
    _levelGen->spawnObstacles(spawns, 1, true);
    resetSpawn(spawns);
}

void DebugLevelSectionScene::test2b()
{
    std::list<SpawnPoint> spawns;
    _levelGen->spawnObstacles(spawns, 2, true);
    resetSpawn(spawns);
}

void DebugLevelSectionScene::test2c()
{
    std::list<SpawnPoint> spawns;
    _levelGen->spawnObstacles(spawns, 3, true);
    resetSpawn(spawns);
}

void DebugLevelSectionScene::test2d()
{
    std::list<SpawnPoint> spawns;
    _levelGen->spawnObstacles(spawns, 4, true);
    resetSpawn(spawns);
}

void DebugLevelSectionScene::test3a()
{
    std::list<SpawnPoint> spawns;
    _levelGen->spawnRollingRock(spawns, 1.0f);
    resetSpawn(spawns);
}

void DebugLevelSectionScene::test3b()
{
    std::list<SpawnPoint> spawns;
    _levelGen->spawnRollingRock(spawns, 0.0f);
    resetSpawn(spawns);
}

void DebugLevelSectionScene::test3c()
{
    std::list<SpawnPoint> spawns;
    _levelGen->spawnTripleRollingRocks(spawns);
    resetSpawn(spawns);
}

void DebugLevelSectionScene::test4a()
{
    std::list<SpawnPoint> spawns;
    _levelGen->spawnPowerUp(spawns);
    resetSpawn(spawns);
}

void DebugLevelSectionScene::test4b()
{
    std::list<SpawnPoint> spawns;
    _levelGen->spawnCoinPattern(spawns);
    resetSpawn(spawns);
}

void DebugLevelSectionScene::exitScene()
{
    _director->replaceScene(DebugMenuScene::create());
}
