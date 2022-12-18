//
//  DebugMenuScene.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#include "DebugMenuScene.h"
//#include "ui/CocosGUI.h"
#include "Debug.h"

USING_NS_AX;

DebugMenuScene::DebugMenuScene()
{
    log("[DEBUG] Create scene: DebugMenu");
}

DebugMenuScene::~DebugMenuScene()
{
    log("[DEBUG] Destroy scene: DebugMenu");
}

static MenuItem* createMenuButton(std::string_view text, Color4B color)
{
    return Debug::createColorButton(text, 32, Vec2(460, 75), color);
}

bool DebugMenuScene::init()
{
    if (!Scene::init()) return false;
    
    auto gameButton = createMenuButton("Game", Color4B(220, 75, 0, 255));
    gameButton->setCallback(AX_CALLBACK_0(DebugMenuScene::presentGameScene, this));
    gameButton->setPosition(Vec2(0, 300));
    
    auto animationSceneButton = createMenuButton("Animation Test", Color4B(45, 215, 0, 255));
    animationSceneButton->setCallback(AX_CALLBACK_0(DebugMenuScene::presentAnimationScene, this));
    animationSceneButton->setPosition(Vec2(0, 200));
    
    auto collisionSceneButton = createMenuButton("Collision Test", Color4B(0, 130, 220, 255));
    collisionSceneButton->setCallback(AX_CALLBACK_0(DebugMenuScene::presentCollisionScene, this));
    collisionSceneButton->setPosition(Vec2(0, 100));
    
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(gameButton);
    menuItems.pushBack(animationSceneButton);
    menuItems.pushBack(collisionSceneButton);
    
    auto menu = Menu::createWithArray(menuItems);
    this->addChild(menu);
    
    return true;
}

void DebugMenuScene::presentGameScene()
{
    _director->replaceScene(GameScene::create());
}

void DebugMenuScene::presentAnimationScene()
{
    _director->replaceScene(DebugAnimationScene::create());
}

void DebugMenuScene::presentCollisionScene()
{
    log("collision scene here");
}
