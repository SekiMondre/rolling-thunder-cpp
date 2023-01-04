//
//  MenuView.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 03/01/23.
//

#include "MenuView.h"
#include "RollingThunder.h"

USING_NS_AX;

const float LEFT_MARGIN = 6.0f;
const float RIGHT_MARGIN = 6.0f;
const float BOTTOM_MARGIN = 6.0f;

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
    
    auto gameTitle = GUI::createMenuImage(ImageAsset::GAME_TITLE);
    auto coinIcon = GUI::createMenuImage(ImageAsset::GOLD_COIN);
    
    auto rankingButton = GUI::createMenuButton(ImageAsset::BUTTON_RANKING_NORMAL, ImageAsset::BUTTON_RANKING_PRESSED);
    auto creditsButton = GUI::createMenuButton(ImageAsset::BUTTON_CREDITS_NORMAL, ImageAsset::BUTTON_CREDITS_PRESSED);
    
    auto musicButton = GUI::createMenuButton(ImageAsset::BUTTON_MUSIC_ON_NORMAL, ImageAsset::BUTTON_MUSIC_ON_PRESSED);
    auto soundButton = GUI::createMenuButton(ImageAsset::BUTTON_SOUND_ON_NORMAL, ImageAsset::BUTTON_SOUND_ON_PRESSED);
    
    const float xLeft = -visibleSize.width * 0.5f;
    const float xRight = visibleSize.width * 0.5f;
    const float yTop = visibleSize.height * 0.5f;
    const float yBot = -visibleSize.height * 0.5f;
    
    gameTitle->setPosition(0.0f, visibleSize.height * 0.5f - 250.0f);
    
    coinIcon->setAnchorPoint(Vec2(1.0f, 1.0f));
    coinIcon->setPosition(yTop - 6.0f, xRight - 10.0f);
    
    rankingButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    rankingButton->setPosition(xLeft + LEFT_MARGIN, yBot + BOTTOM_MARGIN);
    
    creditsButton->setAnchorPoint(Vec2(1.0f, 0.0f));
    creditsButton->setPosition(xRight - RIGHT_MARGIN, yBot + BOTTOM_MARGIN);
    creditsButton->setCallback(AX_CALLBACK_0(MenuView::testCall, this));
    
    musicButton->setAnchorPoint(Vec2(0.0f, 1.0f));
    musicButton->setPosition(-visibleSize.width * 0.5f + 6.0f + 32, yTop - 6.0f - 32 - 32);
    soundButton->setAnchorPoint(Vec2(0.0f, 1.0f));
    soundButton->setPosition(-visibleSize.width * 0.5f + 6.0f + musicButton->getContentSize().width * 2.0f + 6.0f + 32, yBot + BOTTOM_MARGIN - 6.0f - 32 - 32);
    
    Vector<MenuItem*> menuItems;
    menuItems.pushBack(gameTitle);
    menuItems.pushBack(coinIcon);
    menuItems.pushBack(musicButton);
    menuItems.pushBack(soundButton);
    menuItems.pushBack(rankingButton);
    menuItems.pushBack(creditsButton);
    auto menu = Menu::createWithArray(menuItems);
    this->addChild(menu);
    
//    auto coinLabel = Label::create();
    auto coinLabel = ShadowLabel::create();
    coinLabel->setString("00000000000000000");
    coinLabel->setFont("November");
    coinLabel->setAnchorPoint(Vec2(1.0f, 1.0f));
//    coinLabel->setAlignment(TextHAlignment::RIGHT, TextVAlignment::TOP);
    coinLabel->setFontSize(32);
    coinLabel->setPosition(origin.x + visibleSize.width - 14.0f - 42.0f, origin.y + visibleSize.height - 16.0f);
    
    addChild(coinLabel);
    
    return true;
}

void MenuView::testCall()
{
    log("test call");
}
