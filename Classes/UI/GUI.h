//
//  GUI.h
//  RollingThunderCpp
//
//  Created by André Vants on 04/01/23.
//

#ifndef GUI_h
#define GUI_h

#include "axmol.h"

class ShadowLabel;

namespace FontAsset
{
const std::string TAITO = "Taito_Mod";
const std::string DP_COMIC = "DPComicRegular";
const std::string NOVEMBER = "November";
}

namespace GUI
{
ax::MenuItem* createMenuImage(std::string name);
ax::MenuItem* createMenuButton(std::string normalImage, std::string selectedImage);
ax::Label* createLabel(std::string font, float fontSize);
ShadowLabel* createHUDLabel();
}

#endif /* GUI_h */
