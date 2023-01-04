//
//  HUDView.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 04/01/23.
//

#include "HUDView.h"
#include "RollingThunder.h"

USING_NS_AX;

const float LEFT_MARGIN = 25.0f;
const float RIGHT_MARGIN = 25.0f;
const float FIRST_LINE_OFFSET = 70.0f;
const float SECOND_LINE_OFFSET = 130.0f;

HUDView::HUDView()
{
    // Constructor
}

HUDView::~HUDView()
{
    // Destructor
}

bool HUDView::init()
{
    if (!Node::init()) return false;
    
    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    
    auto timeIcon = SpriteLoader::load(ImageAsset::CLOCK_ICON);
    addChild(timeIcon);
    
    auto coinIcon = SpriteLoader::load(ImageAsset::GOLD_COIN);
    addChild(coinIcon);
    
    auto timeLabel = GUI::createHUDLabel();
    addChild(timeLabel);
    timeLabel->setString("0:00.00");
    timeLabel->setAnchorPoint(Vec2(1.0f, 0.0f));
    
    auto coinLabel = GUI::createHUDLabel();
    addChild(coinLabel);
    coinLabel->setString("999999");
    coinLabel->setAnchorPoint(Vec2(1.0f, 0.0f));
    
    auto scoreLabel = GUI::createHUDLabel();
    addChild(scoreLabel);
    scoreLabel->setString("SCORE:");
    scoreLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    auto tr00scoreLabel = GUI::createHUDLabel();
    tr00scoreLabel->setString("9999999");
    tr00scoreLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    addChild(tr00scoreLabel);
    
//    timeLabel->setFontSize(25);
//    coinLabel->setFontSize(26);
//    scoreLabel->setFontSize(27);
//    tr00scoreLabel->setFontSize(28);
    
    timeIcon->setAnchorPoint(Vec2(1.0f, 0.0f));
    timeIcon->setPosition(origin.x + visibleSize.width - RIGHT_MARGIN, origin.y + visibleSize.height - FIRST_LINE_OFFSET);
    
    coinIcon->setAnchorPoint(Vec2(1.0f, 0.0f));
    coinIcon->setPosition(origin.x + visibleSize.width - RIGHT_MARGIN, origin.y + visibleSize.height - SECOND_LINE_OFFSET);
    
    timeLabel->setPosition(origin.x + visibleSize.width - RIGHT_MARGIN - 12.0f - 44.0f, origin.y + visibleSize.height - FIRST_LINE_OFFSET);
    coinLabel->setPosition(origin.x + visibleSize.width - RIGHT_MARGIN - 12.0f - 44.0f, origin.y + visibleSize.height - SECOND_LINE_OFFSET);
    
    scoreLabel->setPosition(origin.x + LEFT_MARGIN, origin.y + visibleSize.height - FIRST_LINE_OFFSET);
    tr00scoreLabel->setPosition(origin.x + LEFT_MARGIN, origin.y + visibleSize.height - SECOND_LINE_OFFSET);
    
    return true;
}
