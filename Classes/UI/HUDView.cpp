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
    auto coinIcon = SpriteLoader::load(ImageAsset::GOLD_COIN);
    
    auto scoreTitleLabel = GUI::createHUDLabel();
    scoreTitleLabel->setString("SCORE:");
    scoreTitleLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    _timeLabel = GUI::createHUDLabel();
    _timeLabel->setString("0:00.00");
    _timeLabel->setAnchorPoint(Vec2(1.0f, 0.0f));
    
    _coinLabel = GUI::createHUDLabel();
    _coinLabel->setString("999999");
    _coinLabel->setAnchorPoint(Vec2(1.0f, 0.0f));
    
    _tr00scoreLabel = GUI::createHUDLabel();
    _tr00scoreLabel->setString("9999999");
    _tr00scoreLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    addChild(_timeLabel);
    addChild(_coinLabel);
    addChild(_tr00scoreLabel);
    addChild(scoreTitleLabel);
    addChild(timeIcon);
    addChild(coinIcon);
    
    timeIcon->setAnchorPoint(Vec2(1.0f, 0.0f));
    timeIcon->setPosition(origin.x + visibleSize.width - RIGHT_MARGIN, origin.y + visibleSize.height - FIRST_LINE_OFFSET);
    
    coinIcon->setAnchorPoint(Vec2(1.0f, 0.0f));
    coinIcon->setPosition(origin.x + visibleSize.width - RIGHT_MARGIN, origin.y + visibleSize.height - SECOND_LINE_OFFSET);
    
    _timeLabel->setPosition(origin.x + visibleSize.width - RIGHT_MARGIN - 12.0f - 44.0f, origin.y + visibleSize.height - FIRST_LINE_OFFSET);
    _coinLabel->setPosition(origin.x + visibleSize.width - RIGHT_MARGIN - 12.0f - 44.0f, origin.y + visibleSize.height - SECOND_LINE_OFFSET);
    
    scoreTitleLabel->setPosition(origin.x + LEFT_MARGIN, origin.y + visibleSize.height - FIRST_LINE_OFFSET);
    _tr00scoreLabel->setPosition(origin.x + LEFT_MARGIN, origin.y + visibleSize.height - SECOND_LINE_OFFSET);
    
    return true;
}

void HUDView::updateScore(Score score)
{
    _tr00scoreLabel->setString(std::to_string(score.points));
    _coinLabel->setString(std::to_string(score.coins));
    
    float gameTime = score.timestamp;
    if (gameTime >= 3600.0f) {
        _timeLabel->setString("w00t");
        return;
    }
    float whole = 0.0f;
    float fraction = std::modf(gameTime, &whole);
    
    int millis = int(fraction * 100.0f);
    int seconds = int(whole) % 60;
    int minutes = int(whole) / 60;
    
    char timeString[10] = {'\0'}; // Minimum is 8
    snprintf(timeString, 10, "%d:%.2d.%.2d", minutes, seconds, millis);
    _timeLabel->setString(timeString);
}
