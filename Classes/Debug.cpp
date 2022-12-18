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
