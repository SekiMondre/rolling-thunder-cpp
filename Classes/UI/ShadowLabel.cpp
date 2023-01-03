//
//  ShadowLabel.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 03/01/23.
//

#include "ShadowLabel.h"

USING_NS_AX;

ShadowLabel::ShadowLabel()
{
    // Constructor
}

ShadowLabel::~ShadowLabel()
{
    // Destructor
}

bool ShadowLabel::init()
{
    if (!Node::init()) return false;
    
    _frontLabel = Label::create();
    _backLabel = Label::create();
    
    _frontLabel->setTextColor(Color4B::WHITE);
    _backLabel->setTextColor(Color4B::BLACK);
    
    _backLabel->setPosition(-3.0f, -3.0f);
    
    addChild(_backLabel);
    addChild(_frontLabel);
    
    return true;
}

void ShadowLabel::setString(std::string text)
{
    _frontLabel->setString(text);
    _backLabel->setString(text);
}

void ShadowLabel::setFont(std::string font)
{
    _frontLabel->setSystemFontName(font);
    _backLabel->setSystemFontName(font);
}

void ShadowLabel::setFontSize(float fontSize)
{
    _frontLabel->setSystemFontSize(fontSize);
    _backLabel->setSystemFontSize(fontSize);
}

void ShadowLabel::setAnchorPoint(const Vec2& anchorPoint)
{
    _frontLabel->setAnchorPoint(anchorPoint);
    _backLabel->setAnchorPoint(anchorPoint);
}
