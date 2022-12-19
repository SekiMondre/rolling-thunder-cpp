//
//  DebugSpriteScene.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#include "DebugSpriteScene.h"
#include "Debug.h"

USING_NS_AX;

DebugSpriteScene::DebugSpriteScene()
{}

DebugSpriteScene::~DebugSpriteScene()
{
    log("[DEBUG] Destroying: Sprite Test");
}

bool DebugSpriteScene::init()
{
    if (!Scene::init()) return false;
    log("[DEBUG] Init scene: Sprite Test");
    
    auto exitButton = Debug::createExitButton(AX_CALLBACK_0(DebugSpriteScene::exitScene, this));
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(exitButton);
    auto menu = Menu::createWithArray(menuItems);
    this->addChild(menu);
    
    return true;
}

void DebugSpriteScene::exitScene()
{
    _director->replaceScene(DebugMenuScene::create());
}
