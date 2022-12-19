//
//  DebugLevelSectionScene.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#include "DebugLevelSectionScene.h"
#include "Debug.h"

USING_NS_AX;

DebugLevelSectionScene::DebugLevelSectionScene()
{}

DebugLevelSectionScene::~DebugLevelSectionScene()
{
    log("[DEBUG] Destroying: Level Modules Test");
}

bool DebugLevelSectionScene::init()
{
    if (!Scene::init()) return false;
    log("[DEBUG] Init scene: Level Modules Test");
    
    auto exitButton = Debug::createExitButton(AX_CALLBACK_0(DebugLevelSectionScene::exitScene, this));
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(exitButton);
    auto menu = Menu::createWithArray(menuItems);
    this->addChild(menu);
    
    return true;
}

void DebugLevelSectionScene::exitScene()
{
    _director->replaceScene(DebugMenuScene::create());
}
