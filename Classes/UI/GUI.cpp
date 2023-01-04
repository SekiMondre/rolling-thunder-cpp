//
//  GUI.cpp
//  RollingThunderCpp
//
//  Created by André Vants on 04/01/23.
//

#include "GUI.h"
#include "RollingThunder.h"

USING_NS_AX;

MenuItem* GUI::createMenuImage(std::string name)
{
    auto item = MenuItemImage::create();
    item->setNormalSpriteFrame(SpriteLoader::loadFrame(name));
    item->setScale(2.0f, 2.0f);
    return item;
}

MenuItem* GUI::createMenuButton(std::string normalImage, std::string selectedImage)
{
    auto item = MenuItemImage::create();
    item->setNormalSpriteFrame(SpriteLoader::loadFrame(normalImage));
    item->setSelectedSpriteFrame(SpriteLoader::loadFrame(selectedImage));
    item->setScale(2.0f, 2.0f);
    return item;
}

Label* GUI::createLabel(std::string font, float fontSize)
{
    auto label = Label::create();
    label->setSystemFontName(font);
    label->setSystemFontSize(fontSize);
    label->setTextColor(Color4B::WHITE);
    return label;
}

ShadowLabel* GUI::createHUDLabel()
{
    auto label = ShadowLabel::create();
    label->setFont(FontAsset::NOVEMBER);
    label->setFontSize(32);
//    label->setFont(FontAsset::DP_COMIC);
//    label->setFontSize(32);
//    label->setFont(FontAsset::TAITO);
//    label->setFontSize(24);
    return label;
}
