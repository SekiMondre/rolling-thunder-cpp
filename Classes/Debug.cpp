//
//  Debug.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 18/12/22.
//

#include "Debug.h"

USING_NS_AX;

MenuItem* Debug::createColorButton(std::string_view text, float fontSize, Vec2 size, Color4B color)
{
    return createColorButton(text, fontSize, size, color, "DPComicRegular");
}

MenuItem* Debug::createColorButton(std::string_view text, float fontSize, Vec2 size, Color4B color, std::string_view font)
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
    label->setColor(Color3B::WHITE);
    label->setSystemFontName(font);
    label->setSystemFontSize(fontSize);
    label->setPosition(size * 0.5);

    auto button = MenuItemSprite::create(normalSprite, selectedSprite);
    button->addChild(label);
    return button;
}

MenuItem* Debug::createExitButton(const ax::ccMenuCallback &callback)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto exitButton = Debug::createColorButton("X", 32, Vec2(64, 64), Color4B::RED);
    exitButton->setPosition(Vec2(-visibleSize.width * 0.5 + 32 + 16, visibleSize.height * 0.5 - 32 - 16));
    exitButton->setCallback(callback);
    return exitButton;
}
