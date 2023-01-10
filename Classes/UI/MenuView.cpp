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

const float START_TEXT_SIZE = 64.0f;
const float START_TEXT_SHADOW_OFFSET = 4.0f;

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
    _creditsButton = GUI::createMenuButton(ImageAsset::BUTTON_CREDITS_NORMAL, ImageAsset::BUTTON_CREDITS_PRESSED);
//    creditsButton->setEnabled(false);
    
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
    
    _creditsButton->setAnchorPoint(Vec2(1.0f, 0.0f));
    _creditsButton->setPosition(xRight - RIGHT_MARGIN, yBot + BOTTOM_MARGIN);
//    _creditsButton->setCallback(AX_CALLBACK_0(MenuView::showCredits, this));
    
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
    menuItems.pushBack(_creditsButton);
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
    
    // START LABEL
    std::string startText = "TOUCH TO START";
    auto mainLabel = GUI::createLabel(FontAsset::DP_COMIC, START_TEXT_SIZE);
    auto shadowLabel_1 = GUI::createLabel(FontAsset::DP_COMIC, START_TEXT_SIZE);
    auto shadowLabel_2 = GUI::createLabel(FontAsset::DP_COMIC, START_TEXT_SIZE);
    
    mainLabel->setString(startText);
    shadowLabel_1->setString(startText);
    shadowLabel_2->setString(startText);
    
    shadowLabel_1->setTextColor(Color4B(66, 15, 27, 255));
    shadowLabel_2->setTextColor(Color4B(66, 15, 27, 255));
    shadowLabel_1->setPosition(-START_TEXT_SHADOW_OFFSET, -START_TEXT_SHADOW_OFFSET);
    shadowLabel_2->setPosition(START_TEXT_SHADOW_OFFSET, -START_TEXT_SHADOW_OFFSET);
    
    _startLabel = Node::create();
    _startLabel->addChild(shadowLabel_1);
    _startLabel->addChild(shadowLabel_2);
    _startLabel->addChild(mainLabel);
    
    _startLabel->setPosition(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.5f - 60.0f);
    _startLabel->setVisible(false);
    addChild(_startLabel);
    
    this->blinkStartLabelWithDelay(0.5f);
    
    return true;
}

void MenuView::blinkStartLabelWithDelay(float d)
{
    _startLabel->stopAllActions();
    auto blink = Sequence::create(DelayTime::create(d),
                                  Show::create(),
                                  DelayTime::create(d),
                                  Hide::create(),
                                  nullptr);
    _startLabel->runAction(RepeatForever::create(blink));
}

void MenuView::setCreditsCallback(const ax::ccMenuCallback &callback)
{
    _creditsButton->setCallback(callback);
}
