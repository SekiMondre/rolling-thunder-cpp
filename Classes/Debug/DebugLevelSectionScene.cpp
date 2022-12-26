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
    float h = Director::getInstance()->getWinSize().height;
    _levelGen = new LevelGenerator(h);
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
//    root->addChild(bg);
    bg->setPosition(origin.x + visibleSize.width * 0.5, 0);
    addChild(bg);
    
    auto root = Node::create();
    root->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, origin.y));
    addChild(root);
    _root = root;
    
//    auto s = Entity(Entity::ENEMY_NORMAL, Vec2(345.0f, 29.5f));
//    log("Entity type: %d, position: {%.1f, %.1f}", s.type, s.position.x, s.position.y);
    
    this->layoutMenu();
    return true;
}

void DebugLevelSectionScene::layoutMenu()
{
    auto visibleSize = _director->getVisibleSize();
    
    auto exitButton = Debug::createExitButton(AX_CALLBACK_0(DebugLevelSectionScene::exitScene, this));
    
    auto button1 = Debug::createColorButton("1", 32, Vec2(64, 64), Color4B::BLUE);
    button1->setCallback(AX_CALLBACK_0(DebugLevelSectionScene::action1, this));
    button1->setPosition(Vec2(visibleSize.width * 0.5 - 32 - 16, -visibleSize.height * 0.5 + 32 + 16));
    
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(exitButton);
    menuItems.pushBack(button1);
    auto menu = Menu::createWithArray(menuItems);
    this->addChild(menu);
}

void DebugLevelSectionScene::action1()
{
    _root->removeAllChildren();
    
    auto spawns = _levelGen->spawnObstacles(4, true);
    for (SpawnPoint e : spawns) {
        auto node = NodeFactory::parseEntity(e);
        node->setPosition(e.position);
        _root->addChild(node);
    }
}

void DebugLevelSectionScene::exitScene()
{
    _director->replaceScene(DebugMenuScene::create());
}
