//
//  DebugLevelGenScene.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#include "DebugLevelGenScene.h"
#include "Debug.h"

USING_NS_AX;

DebugLevelGenScene::DebugLevelGenScene()
{}

DebugLevelGenScene::~DebugLevelGenScene()
{
    log("[DEBUG] Destroying: Level Generator Test");
}

bool DebugLevelGenScene::init()
{
    if (!Scene::init()) return false;
    log("[DEBUG] Init scene: Level Generator Test");
    
    auto exitButton = Debug::createExitButton(AX_CALLBACK_0(DebugLevelGenScene::exitScene, this));
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(exitButton);
    auto menu = Menu::createWithArray(menuItems);
    this->addChild(menu);
    
    return true;
}

void DebugLevelGenScene::exitScene()
{
    _director->replaceScene(DebugMenuScene::create());
}
