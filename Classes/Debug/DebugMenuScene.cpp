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

const std::string DP_COMIC = "DPComicRegular";

DebugMenuScene::DebugMenuScene()
{}

DebugMenuScene::~DebugMenuScene()
{
    log("[DEBUG] Destroying: Debug Menu");
}

static MenuItem* createMenuButton(std::string_view text, Color4B color)
{
    return Debug::createColorButton(text, 32, Vec2(460, 75), color);
}

bool DebugMenuScene::init()
{
    if (!Scene::init()) return false;
    log("[DEBUG] Init scene: Debug Menu");
    
    auto size = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    
    auto title = Label::create();
    title->setString("HT Debug mode – " + Metadata::getAppVersion());
    title->setColor(Color3B::WHITE);
    title->setSystemFontName(DP_COMIC);
    title->setSystemFontSize(32);
    title->setAlignment(TextHAlignment::RIGHT);
    title->setPosition(Vec2(origin.x + size.width * 0.5, origin.y + size.height - 96));
    addChild(title);
    
    auto gameButton = createMenuButton("Game", Color4B(220, 75, 0, 255));
    gameButton->setPosition(Vec2(0, 300));
    gameButton->setCallback(AX_CALLBACK_0(DebugMenuScene::presentGameScene, this));
    
    auto spriteButton = createMenuButton("Sprite Test", Color4B(235, 185, 10, 255));
    spriteButton->setPosition(Vec2(0, 200));
    spriteButton->setCallback(AX_CALLBACK_0(DebugMenuScene::presentSpriteTest, this));
    
    auto animationButton = createMenuButton("Animation Test", Color4B(45, 215, 0, 255));
    animationButton->setPosition(Vec2(0, 100));
    animationButton->setCallback(AX_CALLBACK_0(DebugMenuScene::presentAnimationTest, this));
    
    auto collisionButton = createMenuButton("Collision Test", Color4B(0, 130, 220, 255));
    collisionButton->setPosition(Vec2(0, 0));
    collisionButton->setCallback(AX_CALLBACK_0(DebugMenuScene::presentCollisionTest, this));
    
    auto levelModulesButton = createMenuButton("Level Modules Test", Color4B(245, 145, 0, 255));
    levelModulesButton->setPosition(Vec2(0, -100));
    levelModulesButton->setCallback(AX_CALLBACK_0(DebugMenuScene::presentLevelModulesTest, this));
    
    auto levelGenButton = createMenuButton("Level Generation Test", Color4B(110, 180, 230, 255));
    levelGenButton->setPosition(Vec2(0, -200));
    levelGenButton->setCallback(AX_CALLBACK_0(DebugMenuScene::presentLevelGenTest, this));
    
    auto soundButton = createMenuButton("Sound Test", Color4B(160, 0, 220, 255));
    soundButton->setPosition(Vec2(0, -300));
    soundButton->setCallback(AX_CALLBACK_0(DebugMenuScene::presentSoundTest, this));
    
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(gameButton);
    menuItems.pushBack(spriteButton);
    menuItems.pushBack(animationButton);
    menuItems.pushBack(collisionButton);
    menuItems.pushBack(levelModulesButton);
    menuItems.pushBack(levelGenButton);
    menuItems.pushBack(soundButton);
    auto menu = Menu::createWithArray(menuItems);
    this->addChild(menu);
    
    return true;
}

void DebugMenuScene::presentGameScene()
{
    _director->replaceScene(GameScene::create());
}

void DebugMenuScene::presentSpriteTest()
{
    _director->replaceScene(DebugSpriteScene::create());
}

void DebugMenuScene::presentAnimationTest()
{
    _director->replaceScene(DebugAnimationScene::create());
}

void DebugMenuScene::presentCollisionTest()
{
    _director->replaceScene(DebugCollisionScene::create());
}

void DebugMenuScene::presentLevelModulesTest()
{
    _director->replaceScene(DebugLevelSectionScene::create());
}

void DebugMenuScene::presentLevelGenTest()
{
    _director->replaceScene(DebugLevelGenScene::create());
}

void DebugMenuScene::presentSoundTest()
{
    _director->replaceScene(DebugSoundScene::create());
}
