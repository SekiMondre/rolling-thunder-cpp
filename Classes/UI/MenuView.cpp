//
//  MenuView.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 03/01/23.
//

#include "MenuView.h"
#include "RollingThunder.h"

USING_NS_AX;

MenuView::MenuView()
{
    // Constructor
}

MenuView::~MenuView()
{
    // Destructor
}

bool MenuView::init()
{
    if (!Node::init()) return false;
    
    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    
//    auto gameTitle = SpriteLoader::load(ImageAsset::GAME_TITLE);
    auto gameTitle = MenuItemImage::create();
    gameTitle->setNormalSpriteFrame(SpriteLoader::loadFrame(ImageAsset::GAME_TITLE));
    gameTitle->setScale(2.0f, 2.0f);
    gameTitle->setPosition(0.0f, visibleSize.height * 0.5f - 250.0f);
    
    auto coinIcon = MenuItemImage::create();
    coinIcon->setNormalSpriteFrame(SpriteLoader::loadFrame(ImageAsset::GOLD_COIN));
    coinIcon->setScale(2.0f, 2.0f);
    coinIcon->setAnchorPoint(Vec2(1.0f, 1.0f));
    coinIcon->setPosition(visibleSize.width * 0.5f - 6.0f, visibleSize.height * 0.5f - 10.0f);
    
//    auto coinLabel = Label::create();
    auto coinLabel = ShadowLabel::create();
    coinLabel->setString("00000000000000000");
    coinLabel->setFont("November");
    coinLabel->setAnchorPoint(Vec2(1.0f, 1.0f));
//    coinLabel->setAlignment(TextHAlignment::RIGHT, TextVAlignment::TOP);
    coinLabel->setFontSize(32);
    coinLabel->setPosition(origin.x + visibleSize.width - 14.0f - 42.0f, origin.y + visibleSize.height - 16.0f);
    
    auto rankingButton = MenuItemImage::create();
    rankingButton->setNormalSpriteFrame(SpriteLoader::loadFrame(ImageAsset::BUTTON_RANKING_NORMAL));
    rankingButton->setSelectedSpriteFrame(SpriteLoader::loadFrame(ImageAsset::BUTTON_RANKING_PRESSED));
    rankingButton->setScale(2.0f, 2.0f);
    rankingButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    rankingButton->setPosition(6.0f - visibleSize.width * 0.5f, 6.0f - visibleSize.height * 0.5f);
    
    auto creditsButton = MenuItemImage::create();
    creditsButton->setNormalSpriteFrame(SpriteLoader::loadFrame(ImageAsset::BUTTON_CREDITS_NORMAL));
    creditsButton->setSelectedSpriteFrame(SpriteLoader::loadFrame(ImageAsset::BUTTON_CREDITS_PRESSED));
    creditsButton->setScale(2.0f, 2.0f);
    creditsButton->setAnchorPoint(Vec2(1.0f, 0.0f));
    creditsButton->setPosition(visibleSize.width * 0.5f - 6.0f, 6.0f - visibleSize.height * 0.5f);
    creditsButton->setCallback(AX_CALLBACK_0(MenuView::testCall, this));
    
    auto musicButton = MenuItemImage::create();
    musicButton->setNormalSpriteFrame(SpriteLoader::loadFrame(ImageAsset::BUTTON_MUSIC_ON_NORMAL));
    musicButton->setSelectedSpriteFrame(SpriteLoader::loadFrame(ImageAsset::BUTTON_MUSIC_ON_PRESSED));
    musicButton->setScale(2.0f, 2.0f);
    musicButton->setAnchorPoint(Vec2(0.0f, 1.0f));
    musicButton->setPosition(-visibleSize.width * 0.5f + 6.0f + 32, visibleSize.height * 0.5f - 6.0f - 32 - 32);
    
    auto soundButton = MenuItemImage::create();
    soundButton->setNormalSpriteFrame(SpriteLoader::loadFrame(ImageAsset::BUTTON_SOUND_ON_NORMAL));
    soundButton->setSelectedSpriteFrame(SpriteLoader::loadFrame(ImageAsset::BUTTON_SOUND_ON_PRESSED));
    soundButton->setScale(2.0f, 2.0f);
    soundButton->setAnchorPoint(Vec2(0.0f, 1.0f));
    soundButton->setPosition(-visibleSize.width * 0.5f + 6.0f + musicButton->getContentSize().width * 2.0f + 6.0f + 32, visibleSize.height * 0.5f - 6.0f - 32 - 32);
    
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(gameTitle);
    menuItems.pushBack(coinIcon);
    menuItems.pushBack(musicButton);
    menuItems.pushBack(soundButton);
    menuItems.pushBack(rankingButton);
    menuItems.pushBack(creditsButton);
    auto menu = Menu::createWithArray(menuItems);
    this->addChild(menu);
    
    addChild(coinLabel);
    
    return true;
}

void MenuView::testCall()
{
    log("test call");
}
