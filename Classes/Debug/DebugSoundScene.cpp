//
//  DebugSoundScene.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 19/12/22.
//

#include "DebugSoundScene.h"
#include "Debug.h"

USING_NS_AX;

DebugSoundScene::DebugSoundScene()
{}

DebugSoundScene::~DebugSoundScene()
{
    log("[DEBUG] Destroying: Sound Test");
}

bool DebugSoundScene::init()
{
    if (!Scene::init()) return false;
    log("[DEBUG] Init scene: Sound Test");
    
    auto exitButton = Debug::createExitButton(AX_CALLBACK_0(DebugSoundScene::exitScene, this));
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(exitButton);
    auto menu = Menu::createWithArray(menuItems);
    this->addChild(menu);
    
    return true;
}

void DebugSoundScene::exitScene()
{
    _director->replaceScene(DebugMenuScene::create());
}
