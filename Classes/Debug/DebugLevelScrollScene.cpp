//
//  DebugLevelScrollScene.cpp
//  ConvertUTF
//
//  Created by André Vants on 22/12/22.
//

#include "DebugLevelScrollScene.h"
#include "Debug.h"

USING_NS_AX;

DebugLevelScrollScene::DebugLevelScrollScene()
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
