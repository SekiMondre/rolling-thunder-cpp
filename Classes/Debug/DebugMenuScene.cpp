//
//  DebugMenuScene.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 15/12/22.
//

#include "DebugMenuScene.h"
#include "ui/CocosGUI.h"

USING_NS_AX;

DebugMenuScene::DebugMenuScene()
{
    log("[DEBUG] Scene load: Debug Menu");
}

DebugMenuScene::~DebugMenuScene()
{
    log("[DEBUG] Scene delete: Debug Menu");
}

static MenuItem* createButton(std::string_view text, float fontSize, Vec2 size, Color4B color)
{
    auto selectedColor = Color4B(Color4F(color) * 0.8);
    
    auto normalSprite = DrawNode::create();
    normalSprite->drawSolidRect(Vec2::ZERO, size, color);
    normalSprite->setContentSize(size);
    auto selectedSprite = DrawNode::create();
    selectedSprite->drawSolidRect(Vec2::ZERO, size, selectedColor);
    selectedSprite->setContentSize(size);
    
    auto label = Label::create();
    label->setString(text);
    label->setColor(Color3B::BLACK);
    label->setSystemFontName("DPComicRegular");
    label->setSystemFontSize(fontSize);
    label->setPosition(size * 0.5);

    auto button = MenuItemSprite::create(normalSprite, selectedSprite);
    button->addChild(label);
    return button;
}

static MenuItem* createMenuButton(std::string_view text, Color4B color)
{
    return createButton(text, 32, Vec2(460, 75), color);
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
    log("game scene");
}

void DebugMenuScene::presentAnimationScene()
{
    log("animation scene here");
}

void DebugMenuScene::presentCollisionScene()
{
    log("collision scene here");
}
