//
//  CreditsView.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 04/01/23.
//

#include "CreditsView.h"
#include "RollingThunder.h"

USING_NS_AX;

CreditsView::CreditsView()
{
    // Constructor
}

CreditsView::~CreditsView()
{
    // Destructor
}

bool CreditsView::init()
{
    if (!Node::init()) return false;
    
    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    
    auto center = Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.5f);
    
    auto bg = SpriteLoader::load(ImageAsset::CREDITS_WINDOW);
    addChild(bg);
    bg->setPosition(center);
    
    auto titleLabel = GUI::createLabel(FontAsset::NOVEMBER, 38.0f);
    titleLabel->setString("CREDITS");
    titleLabel->setPosition(center.x, center.y + 428.0f);
    addChild(titleLabel);
    
    auto backButton = GUI::createMenuButton(ImageAsset::BUTTON_BACK_NORMAL, ImageAsset::BUTTON_BACK_PRESSED);
    backButton->setPosition(0.0f, -420.0f);
    auto menu = Menu::createWithItem(backButton);
    addChild(menu);
    
    return true;
}
