//
//  RankingView.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 04/01/23.
//

#include "RankingView.h"
#include "RollingThunder.h"

USING_NS_AX;

RankingView::RankingView()
{
    // Constructor
}

RankingView::~RankingView()
{
    // Destructor
}

bool RankingView::init()
{
    if (!Node::init()) return false;
    
    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    
    auto center = Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.5f);
    
    auto bg = SpriteLoader::load(ImageAsset::RANKING_WINDOW);
    addChild(bg);
    bg->setPosition(center);
    
    auto titleLabel = GUI::createLabel(FontAsset::NOVEMBER, 72.0f);
    titleLabel->setString("RANKING");
    addChild(titleLabel);
    
    auto hiScoreLabel = GUI::createLabel(FontAsset::NOVEMBER, 38.0f);
    hiScoreLabel->setString("HIGH-SCORES");
    addChild(hiScoreLabel);
    
    auto scoreTitleLabel = GUI::createLabel(FontAsset::TAITO, 18.0f);
    scoreTitleLabel->setString("SCORE");
    scoreTitleLabel->setAnchorPoint(Vec2(1.0f, 0.5f));
    addChild(scoreTitleLabel);
    
    auto coinIcon = SpriteLoader::load(ImageAsset::GOLD_COIN);
    coinIcon->setAnchorPoint(Vec2(1.0f, 0.5f));
    addChild(coinIcon);
    
    auto timeIcon = SpriteLoader::load(ImageAsset::CLOCK_ICON);
    timeIcon->setAnchorPoint(Vec2(1.0f, 0.5f));
    addChild(timeIcon);
    
    titleLabel->setPosition(center.x, center.y + 350.0f);
    hiScoreLabel->setPosition(center.x, center.y + 235.0f);
    scoreTitleLabel->setPosition(center.x - 30.0f, center.y + 49.0f);
    coinIcon->setPosition(center.x + 68.0f, center.y + 49.0f);
    timeIcon->setPosition(center.x + 230.0f - 34.0f, center.y + 49.0f);
    
    auto backButton = GUI::createMenuButton(ImageAsset::BUTTON_BACK_NORMAL, ImageAsset::BUTTON_BACK_PRESSED);
    backButton->setPosition(0.0f, -420.0f);
    auto menu = Menu::createWithItem(backButton);
    addChild(menu);
    
    return true;
}
