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

bool DebugCollisionScene::init()
{
    if (!Scene::init()) return false;
    log("[DEBUG] Init scene: Collision Test");
    
    auto exitButton = Debug::createExitButton(AX_CALLBACK_0(DebugCollisionScene::exitScene, this));
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(exitButton);
    auto menu = Menu::createWithArray(menuItems);
    this->addChild(menu);
    
    return true;
}

void DebugCollisionScene::exitScene()
{
    _director->replaceScene(DebugMenuScene::create());
}
